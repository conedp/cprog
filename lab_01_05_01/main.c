#include <stdio.h>
#include <limits.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_OVERFLOW 3

/*
Функция принимает на вход делимое, делитель и 2 указтеля -
на частное и на остаток.
Выполняет целочисленное деление без использования встроенной операции
*/
int divmod(int dividend, int divider, int *quotient, int *reminder)
{   
    long long int product = 0;
    if (divider > dividend)
    {
        *reminder = dividend;
        *quotient = 0;
    }
    else
    {
        *quotient = 1;
        product = divider;
        while (product <= dividend)
        {
            product += divider;
            *quotient += 1;
            if (product > INT_MAX)
                return ERR_OVERFLOW;
        }
        // Вычитаем единицу, так как цикл работает, пока мы не добавим лишнее значение
        *quotient -= 1;
        *reminder = dividend - *quotient * divider;
    }
    return ERR_OK;
}


int main(void)
{
    int a, d;
    int q, r;
    
    printf("Input a, f: ");
    
    if (scanf("%d %d", &a, &d) != 2)
        return ERR_IO;
    
    if (a <= 0 || d <= 0)
        return ERR_RANGE;
    
    if (divmod(a, d, &q, &r) == ERR_OVERFLOW)
        return ERR_OVERFLOW;
    
    printf("a divmod f = %d , rem = %d\n", q, r);
    return ERR_OK;
}
