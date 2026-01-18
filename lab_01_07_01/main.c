#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_OVERFLOW 3

#define ACCURACY 1e-8

/*
Получает на ввод аргумент функции sin(x) и значение точности.
Считает ряд Маклорена до указанной точности.
*/
double row(double x, double eps)
{
    double curr = x;
    int i = 3;
    double s = x;
    while (fabs(curr) > eps)
    {
        curr = (-1) * curr * (x * x) / (i * (i - 1));
        s += curr;
        i += 2;
    }
    return s;
}

int main(void)
{
    double x, eps;
    double s, f, delta, sigma;
    
    printf("Input x, epsilon: ");
    if (scanf("%lf %lf", &x, &eps) != 2)
        return ERR_IO;
    if (eps < 0 || fabs(eps) < ACCURACY || eps > 1)
    return ERR_RANGE;
    
    s = row(x, eps);
    f = sin(x);
    delta = fabs(f - s);
    sigma = delta / fabs(f);
    
    if (fabs(f) < ACCURACY)
        printf("s(x) = %lf ; f(x) = %lf ; delta = %lf ; sigma = 0.000000\n", s, f, delta);
    else
        printf("s(x) = %lf ; f(x) = %lf ; delta = %lf ; sigma = %lf\n", s, f,
        delta, sigma);
    return ERR_OK;
}

