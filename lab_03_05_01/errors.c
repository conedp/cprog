#include "errors.h"

/*
Функция печатает в stdin её описание.
Получает на вход int код ошибки
*/
void print_error(int rc)
{
    if (rc == 1)
        puts("Input error");
    else if (rc == 2)
        puts("Range error");
    else if (rc == 3)
        puts("No suitable error");
    else
        printf("Unknown error: %d\n", rc);
}
