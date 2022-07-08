#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <stdio.h>

/* Данным методом можно находить корни уравнений вида f(x) = 0
* Корень должен располагаться в интервале [a, b]
* Идея метода: Интервал делится пополам,
* вычисляются значения функции в средней точке и на концах
* Для дальнейшего поиска корня (уточнения) оставляем тот интервал
* на границах которого функция меняет знак
* Продолжаем до тех пор, пока длина интервала не станет меньше
* заданной точности
*/

double f(double x);
double eqution(double(*f)(double), double a, double b, double e, double* x);

int main()
{
    double a, b, e, x;
    printf("Enter a: ");
    scanf("%lf", &a);
    printf("Enter b: ");
    scanf("%lf", &b);
    printf("Enter e: ");
    scanf("%lf", &e);
    eqution(f, a, b, e, &x);
    printf("x = %lf", x);
    return 0;
}

double f(double x)
{
    return 2 * sin(x) + 1;
}
double eqution(double(*f)(double), double a, double b, double e, double* x)
{
    while (abs(b - a) > e)
    {
        *x = (f(b) * a - f(a) * b) / (f(b) - f(a));
        if (f(a) * f(*x) > 0) a = *x;
        else b = *x;
    }
    return *x;
}