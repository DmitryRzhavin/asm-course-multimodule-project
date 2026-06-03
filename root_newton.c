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

    root_iterations = 0;

    while (1) {

        root_iterations++;

        double F = f(x) - g(x);
        double dF = df(x) - dg(x);

        double next = x - F / dF;

        if (fabs(next - x) < eps) {
            return next;
        }

        x = next;
    }
}
