#include "get_answer.h"
#include <stdbool.h>
#include "errors.h"

/*
Функция выделяет из строки слово (отсекая пробельные символы и знаки препинания).
Принимает на вход строку, указатель на указатель на первый символ слова и указатель на указатель на последний символ слова
*/
void get_next_word(char *str, char **pbeg, char **pend)
{
    *pbeg = NULL;
    *pend = NULL;
    char *pcur = str;
    while (*pcur && strchr(WORD_DIVIDERS, *pcur))
        pcur += 1;
    if (!*pcur)
        return;
    *pbeg = pcur;
    while (!strchr(WORD_DIVIDERS, *pcur) && *pcur)
        pcur += 1;
    *pend = pcur;
}


/*
Функция копирует слово между указателями в другую строку. Не позволяет скопировать слово блиной больше данной.
Принимает на вход указатели const char на начало и конец слова, char* строку, в которую копируется слово и size_t максимальный размер слова.
*/
int copy_word(const char *pbeg, const char *pend, char *word, size_t word_size)
{
    if ((size_t) (pend - pbeg) > word_size)
        return ERR_BUF_TOO_SMALL;
    while (pbeg < pend)
    {
        *word = *pbeg;
        pbeg += 1;
        word += 1;
    }
    *word = 0;
    return OK;
}


/*
Функция разбивает строку на слова и записывает их в массив.
Принимает на вход char* строку, char[][WORD_LEN] массив слов и size_tуказатель на количество слов в массиве
*/
int parse_string(char *str, char words[][WORD_LEN], size_t *words_n)
{
    char *pbeg, *pend, *pcur = str;
    size_t n = 0;
    int rc = OK;
    while (pcur && *pcur && rc == OK)
    {
        get_next_word(pcur, &pbeg, &pend);
        if (pbeg)
        {
            if (n < N)
            {
                rc = copy_word(pbeg, pend, words[n], sizeof(words[n]));
                if (!rc)
                    n += 1;
            }
            else
                rc = ERR_TOO_MUCH_WORDS;
        }
        pcur = pend;
    }
    if (!rc)
        *words_n = n;
    return rc;
}


/*
Функция проверяет, входит ли слово в массив слов.
Принимает на вход char* строку, (char*)[WORD_LEN] массив слов и size_t его длину
*/
size_t count_str_in_arr(const char *str, char words[][WORD_LEN], size_t words_n)
{
    size_t counter = 0;
    for (size_t i = 0; i < words_n; i++)
        if (!strcmp(str, words[i]))
            counter += 1;
    return counter;
}


/*
Функция формирует новый массив из элементов, встретившихся в двух других массивах единожды.
Принимает на вход (char*)[WORD_LEN] первый массив-источник и его длину, (char*)[WORD_LEN] второй массив-источник и его длину, (char*)[WORD_LEN] формируемый массив и указатель на его длину
*/
void form_array(char words_1_src[][WORD_LEN], size_t words_1_src_n, char words_2_src[][WORD_LEN], size_t words_2_src_n, char words_dst[][WORD_LEN], size_t *words_dst_n)
{
    size_t dst_curr_i = 0;
    for (size_t i = 0; i < words_1_src_n; i++)
        if (count_str_in_arr(words_1_src[i], words_1_src, words_1_src_n) + count_str_in_arr(words_1_src[i], words_2_src, words_2_src_n) == 1)
        {
            strncpy(words_dst[dst_curr_i], words_1_src[i], WORD_LEN);
            dst_curr_i += 1;
        }
    
    for (size_t i = 0; i < words_2_src_n; i++)
        if (count_str_in_arr(words_2_src[i], words_1_src, words_1_src_n) + count_str_in_arr(words_2_src[i], words_2_src, words_2_src_n) == 1)
        {
            strncpy(words_dst[dst_curr_i], words_2_src[i], WORD_LEN);
            dst_curr_i += 1;
        }
    *words_dst_n = dst_curr_i;
}
