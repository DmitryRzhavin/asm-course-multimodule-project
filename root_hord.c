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
double root_hord(afunc *f, afunc *g, double a, double b, double eps) {
    double fa = f(a) - g(a);
    double fb = f(b) - g(b);

    double x = (a * fb - b * fa) / (fb - fa);
    double fx = f(x) - g(x);

    root_iterations = 1;

    while (fabs(fx) >= eps) {
        if (fa * fx < 0.0) {
            b = x;
            fb = fx;
        } else {
            a = x;
            fa = fx;
        }

        x = (a * fb - b * fa) / (fb - fa);
        fx = f(x) - g(x);

        root_iterations++;
    }

    return x;
}
