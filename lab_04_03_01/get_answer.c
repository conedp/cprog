#include "get_answer.h"
#include "errors.h"


/*
Функция разбивает строку на слова и записывает их в массив.
Принимает на вход char* строку, char[][WORD_LEN] массив слов и size_tуказатель на количество слов в массиве
*/
int parse_string(char *str, char words[][WORD_LEN], size_t *words_n)
{
    char *pcur;
    size_t n = 0;
    int rc = OK;
    pcur = strtok(str, WORD_DIVIDERS);
    while (pcur && rc == OK)
    {
        if (n < N)
        {
            if (strlen(pcur) >= WORD_LEN)
                rc = ERR_BUF_TOO_SMALL;
            else
                strncpy(words[n], pcur, sizeof(words[n]));
            n += 1;
        }
        else
            rc = ERR_TOO_MUCH_WORDS;
        pcur = strtok(NULL, WORD_DIVIDERS);
    }
    if (!rc)
        *words_n = n;
    return rc;
}


/*
Функция проверяет, входит ли символ в массив.
Принимает на вход char символ, сhar[] массив символов и size_t его длину
*/
bool is_char_in_arr(char sym, const char word[], size_t word_n)
{
    for (size_t i = 0; i < word_n; i++)
        if (sym == word[i])
            return true;
    return false;
}


/*
Функция удаляет символ из массива по индексу.
Принимает на вход char[] массив, size_t указатель на его длину и size_t индекс
*/
int delete_by_ind(char word[], size_t *word_n, size_t index)
{
    if (index >= *word_n)
        return ERR_RANGE;
    for (size_t i = index + 1; i < *word_n; i++)
        word[i - 1] = word[i];
    *word_n -= 1;
    word[*word_n] = 0;
    return OK;
}


/*
Функция удаляет из массива неуникальные символы и возвращает указатель на него.
Принимает на вход char[] массив символов и size_t указатель на его длину
*/
char *delete_duplicates(char word[], size_t *word_n)
{
    for (size_t i = 0; i < *word_n; i++)
        if (is_char_in_arr(word[i], word, i))
        {
            if (delete_by_ind(word, word_n, i))
                return NULL;
            i -= 1;
        }
    return word;
}


/*
Функция заполняет строку из массива словами, отличными от последнего, в обратном порядке через пробел.
Принимает на вход char* заполняемую строку, (char*)[WORD_LEN] массив слов и size_t его размер
*/
int fill_string(char *dst, char words[][WORD_LEN], size_t words_n)
{
    size_t curr_word_len, dst_len = 0;
    if (words_n > 1)
    {
        for (size_t i = words_n - 2; i < words_n; i--)
        {
            if (strcmp(words[i], words[words_n - 1]))
            {
                curr_word_len = strlen(words[i]);
                if (!delete_duplicates(words[i], &curr_word_len))
                    return ERR_RANGE;
                if (dst_len + curr_word_len < STR_LEN)
                {
                    strncat(dst, words[i], STR_LEN - dst_len);
                    dst_len += curr_word_len + 1;
                }
                else
                    return ERR_BUF_TOO_SMALL;
                strcat(dst, " ");
            }
        }
        // Удаление последнего пробела
        dst_len = strlen(dst);
        if (dst_len != 0)
            dst[dst_len - 1] = 0;
    }
    return OK;
}
