#include "errors.h"
#include "film_array.h"
#include "film.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE 10
#define TITLE_ARG "title"
#define NAME_ARG "name"
#define YEAR_ARG "year"
#define ARG_LEN 25


int main(int argc, char **argv)
{
    FILE *f;
    struct film_t films[N_MAX];
    size_t films_n;
    struct film_t *film_found, film_to_search;
    int rc = OK;
    int sorted_by = TITLE;  // 0 - title, 1 - name, 2 - year
    long year_tmp;
    char arg_buf[ARG_LEN + 1];
    char *year_p_tmp;

    // Проверка на корректность вызова
    if (argc < 3 || argc > 4)
    {
        //print_usage();
        return ERR_ARGS;
    }
    // Открытие файла
    f = fopen(argv[1], "r");
    if (!f)
    {
        rc = ERR_IO;
        //puts("File can't be opened");
        //print_usage();
        return rc;
    }
    // Анализ аргумента, отвечающего за поле, по которому производится сортировка
    if (strncmp(argv[2], TITLE_ARG, strlen(TITLE_ARG)) == 0)
        sorted_by = TITLE;
    else if (strncmp(argv[2], NAME_ARG, strlen(NAME_ARG)) == 0)
        sorted_by = NAME;
    else if (strncmp(argv[2], YEAR_ARG, strlen(YEAR_ARG)) == 0)
        sorted_by = YEAR;
    else
        return ERR_ARGS;
    // Копирование аргумента со строкой (годом) поиска в переменную
    if (argc == 4)
    {
        if (strlen(argv[3]) > ARG_LEN)
            return ERR_ARGS;
        strncpy(arg_buf, argv[3], ARG_LEN + 1);
    }

    // Чтение массива структур с сортировкой
    if (sorted_by == TITLE)
        rc = fa_read_with_sort_by_given(f, films, N_MAX, &films_n, film_cmp_by_title);
    else if (sorted_by == NAME)
        rc = fa_read_with_sort_by_given(f, films, N_MAX, &films_n, film_cmp_by_name);
    else if (sorted_by == YEAR)
        rc = fa_read_with_sort_by_given(f, films, N_MAX, &films_n, film_cmp_by_year);
    if (rc != OK)
    {
        //print_error(rc);
        return rc;
    }
    fclose(f);

    // Анализ количества аргументов для выбора действия
    // Вывод всего массива данных
    if (argc == 3)
    {
        fa_print(stdout, films, films_n);
        return OK;
    }
    // Нахождение двоичным поиском фильма по ключу и вывод данных о нём
    if (sorted_by == TITLE)
    {
        strncpy(film_to_search.title, arg_buf, TITLE_LEN + 1);
        film_found = fa_bin_search_by_given(films, films_n, &film_to_search, film_cmp_by_title);
    }
    else if (sorted_by == NAME)
    {
        strncpy(film_to_search.name, arg_buf, NAME_LEN + 1);
        film_found = fa_bin_search_by_given(films, films_n, &film_to_search, film_cmp_by_name);
    }
    else if (sorted_by == YEAR)
    {
        year_tmp = strtol(arg_buf, &year_p_tmp, BASE);
        if (*year_p_tmp)
            rc = ERR_ARGS;
        else
        {
            film_to_search.year = (int) year_tmp;
            film_found = fa_bin_search_by_given(films, films_n, &film_to_search, film_cmp_by_year);
        }
    }
    if (rc != OK)
    {
        //print_error(rc);
        return rc;
    }
    // Вывод результата поиска
    if (film_found)
        film_print(stdout, film_found);
    else
        puts("Not found");

    return OK;
}
