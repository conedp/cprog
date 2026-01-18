#include "io.h"
#include <stdio.h>
#include "constants.h"
#include "errors.h"

/*
Функция считывает строку из stdin.
Принимает на вход указатель на строку и size_t её максимальный размер.
*/
int get_line(char *buf, size_t buf_size)
{
    if (!fgets(buf, buf_size, stdin))
        return ERR_IO;
    char *enter = strrchr(buf, '\n');
    if (enter)
        *enter = 0;
    else
        return ERR_IO;
    return OK;
}
