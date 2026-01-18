#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define ACCURACY 1e-8

/*
Считывает данные из ввода по одному числу до первого отрицательного
и возвращает число вида exp(1/((x1 + 1)*(x2 + 2)*...*(xn + n)))
*/
int row(double *result)
{
    double x;
    int i = 1;
    
    *result = exp(1);
    
    while (scanf("%lf", &x) == 1 && x >= 0)
    {
        *result = pow(*result, (1 / (x + i)));
        i++;
    }
    // Если не было введено ни одного положительного числа ИЛИ если после ввода положительного числа
    // было введено не число (в переменной x осталось положительное значение)
    if (i == 1 || x >= 0)
        return ERR_IO;
    else
        return ERR_OK;
}

int main(void)
{
    double g;
    
    printf("Input numbers, input will be ended when negative found: ");
    if (row(&g) == ERR_IO)
        return ERR_IO;
    
    printf("g(x) = %lf\n", g);
    
    return ERR_OK;
}

