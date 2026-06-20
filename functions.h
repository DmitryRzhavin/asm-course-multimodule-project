/*
Объявления функций для вычисления значений кривых,
поиска корней и вычисления определённых интегралов
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* Тип функции с вещественным аргументом */
typedef double afunc(double);

/* Исходные функции */
double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);
double f5(double x);

/* Производные */
double df1(double x);
double df2(double x);
double df3(double x);
double df4(double x);
double df5(double x);

/* Разности */
double f12(double x);
double f13(double x);

/* Метод хорд */
double root_hord(afunc *f, afunc *g, double a, double b, double eps);

/* Метод Ньютона */
double root_newton(afunc *f, afunc *g, afunc *df, afunc *dg, double a, double b, double eps);

double integral(afunc *f, double a, double b, double eps);

/* Вычисление количества итераций для последнего вызова root() */
extern int root_iterations;

#endif
