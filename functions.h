/*
Объявления функций для вычисления значений кривых,
поиска корней и вычисления определённых интегралов
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* Тип функции с вещественным аргументом */
typedef double afunc(double);

double f1(double x);
double f2(double x);
double f3(double x);

double f12(double x);
double f13(double x);

double root(afunc *f, afunc *g, double a, double b, double eps);

double integral(afunc *f, double a, double b, double eps);

/* Вычисление количества итераций для последнего вызова root() */
extern int root_iterations;

#endif