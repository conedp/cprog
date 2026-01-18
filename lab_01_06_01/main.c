#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_OVERFLOW 3
#define ERR_NOT_A_TRIANGLE 4

#define ACCURACY 1e-8

/*
Функция принимает на вход координаты трёх точек на плоскости.
Возвращает площадь треугольника, образованного точками
*/
double triangle_area(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double side_12 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    double side_13 = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    double side_23 = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    double p = (side_12 + side_13 + side_23) / 2;
    double s = sqrt(p * (p - side_12) * (p - side_13) * (p - side_23));
    return s;
}

int main(void)
{
    double x_a, y_a, x_b, y_b, x_c, y_c;
    double s;
    
    printf("Input x_a, y_a, x_b, y_b, x_c, y_c: ");
    
    if (scanf("%lf %lf %lf %lf %lf %lf", &x_a, &y_a, &x_b, &y_b, &x_c, &y_c) != 6)
        return ERR_IO;
    
    s = triangle_area(x_a, y_a, x_b, y_b, x_c, y_c);
    
    if (fabs(s) < ACCURACY)
        return ERR_NOT_A_TRIANGLE;
    if (! isfinite(s))
        return ERR_OVERFLOW;
    
    printf("Area of triangle = %lf\n", s);
    return 0;
}
