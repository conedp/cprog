#include "errors.h"

/*
Функция печатает в stdin её описание.
Получает на вход int код ошибки
*/
void print_error(int rc)
{
    if (rc == ERR_IO)
        puts("Input error");
    else if (rc == ERR_RANGE)
        puts("Range error");
    else if (rc == ERR_EMPTY_MATRIX)
        puts("Empty matrix error");
    else
        printf("Unknown error: %d\n", rc);
}
