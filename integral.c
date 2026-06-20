/*
Вычисление определённых интегралов
методом Симпсона (парабол).

При удвоении числа разбиений n значения функции
в старых узлах переиспользуются, а не вычисляются заново.
*/

#include "functions.h"
#include <math.h>

/*
Вычисляет определённый интеграл функции f
на отрезке [a, b] по формуле Симпсона.

Точность контролируется правилом Рунге (p = 1/15):
    |I - I_{2n}| ≈ 1/15 * |I_{2n} - I_n|
*/
double integral(afunc *f, double a, double b, double eps) {
    int n = 10;
    if (n % 2 != 0) {
        n++;
    }

    double h = (b - a) / n;

    /* Вычисляем начальную сумму S_n и сумму нечётных узлов sum_odd */
    double S = f(a) + f(b);
    double sum_odd = 0.0;

    for (int i = 1; i < n; i++) {
        double val = f(a + i * h);
        if (i % 2 == 0) {
            S += 2.0 * val;
        } else {
            S += 4.0 * val;
            sum_odd += val;
        }
    }

    double In = S * h / 3.0;

    while (1) {
        double h_new = h / 2.0;
        double sum_new_mid = 0.0;

        /* Суммируем ТОЛЬКО в новых средних точках */
        for (int i = 0; i < n; i++) {
            sum_new_mid += f(a + (2 * i + 1) * h_new);
        }

        /* S_{2n} = S_n - 2*sum_odd + 4*sum_new_mid */
        double S_new = S - 2.0 * sum_odd + 4.0 * sum_new_mid;
        double I2n = S_new * h_new / 3.0;

        /* Правило Рунге для Симпсона: p = 1/15 */
        if (fabs(I2n - In) / 15.0 < eps) {
            return I2n;
        }

        /* Обновляем переменные для следующей итерации */
        In = I2n;
        S = S_new;
        sum_odd = sum_odd + sum_new_mid;
        h = h_new;
        n *= 2;
    }
}
