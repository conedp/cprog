#include <stdio.h>
#include <stddef.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

/*
Функция выводит разложение n на простые множители в формате n = m1 * m2 * ... * mk
*/
int print_simple(int n)
{
    int curr;
    
    if (n == 1)
        return ERR_OK;
    
    printf("n = ");
    while (n > 1)
    {
        // Найдём наименьший делитель числа n
        size_t i = 2;
        while ((size_t) n % i != 0)
        {
            i++;
        }
        // Записываем (и выводим) делитель
        curr = i;
        // Делим n на найдённый делитель
        n /= curr;
        if (n != 1)
        {
            printf("%d * ", curr);
        }
        else
        {
            printf("%d\n", curr);
        }
    }
    return ERR_OK;
}


int main(void) 
{
    int n;
    
    printf("Input n: ");
    if (scanf("%d", &n) != 1)
    {
        return ERR_IO;
    }
    if (n <= 0)
        return ERR_RANGE;
    
    print_simple(n);
    
    return ERR_OK;
}
