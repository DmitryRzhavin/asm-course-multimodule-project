/*
Поиск точки пересечения двух функций
методом хорд (секущих)
*/

#include "functions.h"
#include <math.h>

/*
Количество итераций, выполненных
последним вызовом root()
*/
int root_iterations = 0;

/*
Находит корень уравнения

    f(x) = g(x)

на отрезке [a, b] с точностью eps

Используется при этом метод хорд
*/
double root(afunc *f, afunc *g, double a, double b, double eps) {
    double fa;
    double fb;
    double fx;
    double x;

    root_iterations = 0;

    while (1) {
        root_iterations++;

        fa = f(a) - g(a);
        fb = f(b) - g(b);

        x = (a * fb - b * fa) / (fb - fa);

        fx = f(x) - g(x);

        if (fabs(fx) < eps) {
            return x;
        }

        if (fa * fx < 0.0) {
            b = x;
        } else {
            a = x;
        }
    }
}
