/*
Вычисление определённых интегралов
методом Симпсона
*/

#include "functions.h"
#include <math.h>

/*
Вычисляет приближённое значение интеграла
по формуле Симпсона для фиксированного
числа разбиений n
*/
static double simpson(afunc *f, double a, double b, int n) {
  double h = (b - a) / n;

  double sum = f(a) + f(b);

  for (int i = 1; i < n; i++) {
    double x = a + i * h;

    if (i % 2 == 0)
      sum += 2.0 * f(x);
    else
      sum += 4.0 * f(x);
  }

  return sum * h / 3.0;
}

/*
Вычисляет определённый интеграл функции f
на отрезке [a, b].

Точность контролируется правилом Рунге:

    |I(2n) - I(n)| / 15 < eps
*/
double integral(afunc *f, double a, double b, double eps) {
  int n = 10;

  if (n % 2 != 0)
    n++;

  double I1;
  double I2;

  while (1) {
    I1 = simpson(f, a, b, n);

    n *= 2;

    I2 = simpson(f, a, b, n);

    if (fabs(I2 - I1) / 15.0 < eps)
      return I2;
  }
}