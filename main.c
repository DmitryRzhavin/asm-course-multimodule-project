#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include "functions.h"

/* Макрос для выбора метода поиска корней на этапе препроцессирования */
#ifdef USE_NEWTON
#define ROOT(f, g, df, dg, a, b, eps) root_newton(f, g, df, dg, a, b, eps)
#else
#define ROOT(f, g, df, dg, a, b, eps) root_hord(f, g, a, b, eps)
#endif

/* Прототипы функций */
static void print_help(const char *prog_name);
static void handle_test_root(const char *arg);
static void handle_test_integral(const char *arg);
static void print_roots(void);
static void print_iterations(void);
static void compute_area(void);
static afunc *get_func(int idx);
#ifdef USE_NEWTON
static afunc *get_dfunc(int idx);
#endif

/* Глобальные переменные для хранения результатов поиска корней */
static double root_12 = 0.0, root_13 = 0.0, root_23 = 0.0;
static int iter_12 = 0, iter_13 = 0, iter_23 = 0;

/* Функция, которая один раз находит все корни и сохраняет итерации */
static void find_all_roots(void) {
    root_12 = ROOT(f1, f2, df1, df2, 0.0, 2.0, 1e-6);
    iter_12 = root_iterations;

    root_13 = ROOT(f1, f3, df1, df3, -2.0, 1.0, 1e-6);
    iter_13 = root_iterations;

    root_23 = ROOT(f2, f3, df2, df3, -1.5, 0.5, 1e-6);
    iter_23 = root_iterations;
}

int main(int argc, char *argv[]) {
    static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                           {"root", no_argument, 0, 'r'},
                                           {"iterations", no_argument, 0, 'i'},
                                           {"test-root", required_argument, 0, 'R'},
                                           {"test-integral", required_argument, 0, 'I'},
                                           {0, 0, 0, 0}};

    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "hriR:I:", long_options, &option_index)) != -1) {
        switch (opt) {
        case 'h':
            print_help(argv[0]);
            return 0;
        case 'r':
            find_all_roots();
            print_roots();
            return 0;
        case 'i':
            find_all_roots();
            print_iterations();
            return 0;
        case 'R':
            handle_test_root(optarg);
            return 0;
        case 'I':
            handle_test_integral(optarg);
            return 0;
        default:
            print_help(argv[0]);
            return 1;
        }
    }

    /* Если опций нет — вычисляем площадь фигуры */
    find_all_roots();
    compute_area();
    return 0;
}

static void print_help(const char *prog_name) {
    printf("Usage: %s [OPTIONS]\n", prog_name);
    printf("Options:\n");
    printf("  -h, --help              Show this help message\n");
    printf("  -r, --root              Print intersection points (abscissas)\n");
    printf("  -i, --iterations        Print iteration counts for root finding\n");
    printf("  -R, --test-root ARG     Test root function (F1:F2:A:B:E:R)\n");
    printf("  -I, --test-integral ARG Test integral function (F:A:B:E:R)\n");
}

static afunc *get_func(int idx) {
    switch (idx) {
    case 1:
        return f1;
    case 2:
        return f2;
    case 3:
        return f3;
    case 4:
        return f4;
    case 5:
        return f5;
    default:
        return NULL;
    }
}

#ifdef USE_NEWTON
static afunc *get_dfunc(int idx) {
    switch (idx) {
    case 1:
        return df1;
    case 2:
        return df2;
    case 3:
        return df3;
    case 4:
        return df4;
    case 5:
        return df5;
    default:
        return NULL;
    }
}
#endif

static void handle_test_root(const char *arg) {
    int f1_idx, f2_idx;
    double a, b, eps, expected;

    if (sscanf(arg, "%d:%d:%lf:%lf:%lf:%lf", &f1_idx, &f2_idx, &a, &b, &eps, &expected) != 6) {
        fprintf(stderr, "Invalid format for --test-root. Expected F1:F2:A:B:E:R\n");
        return;
    }

    afunc *f = get_func(f1_idx);
    afunc *g = get_func(f2_idx);
    if (!f || !g) {
        fprintf(stderr, "Invalid function index\n");
        return;
    }

#ifdef USE_NEWTON
    afunc *df = get_dfunc(f1_idx);
    afunc *dg = get_dfunc(f2_idx);
#endif

    double result = ROOT(f, g, df, dg, a, b, eps);
    double abs_err = fabs(result - expected);
    double rel_err = (fabs(expected) > 1e-15) ? abs_err / fabs(expected) : 0.0;

    printf("%.5f %.5f %.7f\n", result, abs_err, rel_err);
}

static void handle_test_integral(const char *arg) {
    int f_idx;
    double a, b, eps, expected;

    if (sscanf(arg, "%d:%lf:%lf:%lf:%lf", &f_idx, &a, &b, &eps, &expected) != 5) {
        fprintf(stderr, "Invalid format for --test-integral. Expected F:A:B:E:R\n");
        return;
    }

    afunc *f = get_func(f_idx);
    if (!f) {
        fprintf(stderr, "Invalid function index\n");
        return;
    }

    double result = integral(f, a, b, eps);
    double abs_err = fabs(result - expected);
    double rel_err = (fabs(expected) > 1e-15) ? abs_err / fabs(expected) : 0.0;

    printf("%.5f %.5f %.7f\n", result, abs_err, rel_err);
}

/* Вывод только чисел (абсцисс), без лишнего текста */
static void print_roots(void) { printf("%.6f %.6f %.6f\n", root_12, root_13, root_23); }

/* Вывод только чисел (количества итераций), без лишнего текста */
static void print_iterations(void) { printf("%d %d %d\n", iter_12, iter_13, iter_23); }

static void compute_area(void) {
    /*
     * TODO: Реализовать вычисление площади для вашего варианта.
     * Точки пересечения уже найдены и лежат в root_12, root_13, root_23.
     */
    printf("Area computation for your variant is not fully implemented.\n");
    printf("Intersection points: %.6f, %.6f, %.6f\n", root_12, root_13, root_23);
}
