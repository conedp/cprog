#include "errors.h"
#include <stdio.h>

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
    else if (rc == ERR_BUF_TOO_SMALL)
        puts("Too big word error");
    else if (rc == ERR_TOO_MUCH_WORDS)
        puts("Too many words error");
    else
        printf("Unknown error: %d\n", rc);
}
