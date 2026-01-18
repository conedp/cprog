#include "io.h"
#include "errors.h"
#include <stdio.h>

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


/*
Функция выводит слова из массива в строку через пробел.
Принимает на вход массив строк и size_t его длину
*/
void print_word_array(char words[][WORD_LEN], size_t words_n)
{
    for (size_t i = 0; i < words_n; i++)
        printf("%s ", words[i]);
    printf("\n");
}
