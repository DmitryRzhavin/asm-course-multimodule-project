// Поиск корня методом касательных (Ньютона)

#include "functions.h"
#include <math.h>

/*
Количество итераций, выполненных
последним вызовом root()
*/
int root_iterations = 0;

double root_newton(afunc *f, afunc *g, afunc *df, afunc *dg, double a, double b, double eps) {
    double x = (a + b) / 2.0;

    root_iterations = 1;

    double F = f(x) - g(x);
    double dF = df(x) - dg(x);

    double next = x - F / dF;

    while (fabs(next - x) >= eps) {
        x = next;

        F = f(x) - g(x);
        dF = df(x) - dg(x);

        next = x - F / dF;

        root_iterations++;
    }

    return next;
}
