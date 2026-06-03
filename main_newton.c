/*
Основной модуль программы

Поддерживает:
 - вычисление площади фигуры
 - вывод числа итераций метода касательных
 - тестирование функций root() и integral()
*/

#include "functions.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Вывод справки */
static void print_help(void) {
    printf("Usage:\n");
    printf("  ./integral                          calculate area\n");
    printf("  ./integral -h, --help               show help\n");
    printf("  ./integral -r, --root               print roots\n");
    printf("  ./integral -i, --iterations         print iteration counts\n");
    printf("  ./integral -R, --test-root ARG      test root\n");
    printf("  ./integral -I, --test-integral ARG  test integral\n");
}

/* Вычисление относительной ошибки */
static double rel_error(double value, double exact) {
    if (fabs(exact) < 1e-15) {
        return 0.0;
    }

    return fabs(value - exact) / fabs(exact);
}

/*
Возвращает указатель на функцию по её номеру:
  1 -> f1
  2 -> f2
  3 -> f3
*/
static afunc *get_function(int n) {
    switch (n) {
    case 1:
        return f1;

    case 2:
        return f2;

    case 3:
        return f3;

    default:
        return NULL;
    }
}

static afunc *get_derivative(int n) {
    switch (n) {

    case 1:
        return df1;

    case 2:
        return df2;

    case 3:
        return df3;

    default:
        return NULL;
    }
}

int main(int argc, char *argv[]) {
    double eps_root = 1e-6;
    double eps_int = 1e-6;

    if (argc > 1) {

        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {

            print_help();
            return 0;
        }

        if (strcmp(argv[1], "-R") == 0 || strcmp(argv[1], "--test-root") == 0) {

            if (argc != 3) {
                fprintf(stderr, "Wrong arguments\n");
                return 1;
            }

            int f1n;
            int f2n;

            double a;
            double b;
            double eps;
            double exact;

            if (sscanf(argv[2], "%d:%d:%lf:%lf:%lf:%lf", &f1n, &f2n, &a, &b, &eps, &exact) != 6) {

                fprintf(stderr, "Wrong format\n");
                return 1;
            }

            afunc *f = get_function(f1n);
            afunc *g = get_function(f2n);

            if (f == NULL || g == NULL) {
                fprintf(stderr, "Wrong function number\n");
                return 1;
            }

            afunc *df = get_derivative(f1n);
            afunc *dg = get_derivative(f2n);

            double result = root_newton(f, g, df, dg, a, b, eps);

            printf("%.10f\n", result);
            printf("%.10f\n", fabs(result - exact));
            printf("%.10f\n", rel_error(result, exact));

            return 0;
        }

        if (strcmp(argv[1], "-I") == 0 || strcmp(argv[1], "--test-integral") == 0) {

            if (argc != 3) {
                fprintf(stderr, "Wrong arguments\n");
                return 1;
            }

            int fn;

            double a;
            double b;
            double eps;
            double exact;

            if (sscanf(argv[2], "%d:%lf:%lf:%lf:%lf", &fn, &a, &b, &eps, &exact) != 5) {

                fprintf(stderr, "Wrong format\n");
                return 1;
            }

            afunc *f = get_function(fn);

            if (f == NULL) {
                fprintf(stderr, "Wrong function number\n");
                return 1;
            }

            double result = integral(f, a, b, eps);

            printf("%.10f\n", result);
            printf("%.10f\n", fabs(result - exact));
            printf("%.10f\n", rel_error(result, exact));

            return 0;
        }
    }

    int iterA;
    int iterD;
    int iterC;

    double xA = root_newton(f1, f2, df1, df2, 4.0, 6.0, eps_root);
    iterA = root_iterations;

    double xD = root_newton(f1, f3, df1, df3, 1.0, 2.0, eps_root);
    iterD = root_iterations;

    double xC = root_newton(f2, f3, df2, df3, 4.0, 5.0, eps_root);
    iterC = root_iterations;

    if (argc > 1) {

        if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "--root") == 0) {

            printf("A = %.10f\n", xA);
            printf("D = %.10f\n", xD);
            printf("C = %.10f\n", xC);

            return 0;
        }

        if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--iterations") == 0) {

            printf("f1-f2: %d\n", iterA);
            printf("f1-f3: %d\n", iterD);
            printf("f2-f3: %d\n", iterC);

            return 0;
        }
    }

    double S1 = integral(f13, xD, xC, eps_int);
    double S2 = integral(f12, xC, xA, eps_int);

    double area = S1 + S2;

    printf("Area = %.10f\n", area);

    return 0;
}
