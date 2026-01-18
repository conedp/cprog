#include "film_array.h"
#include "film.h"
#include <assert.h>
#include <string.h>


/*
Функция находит индекс для вставки фильма с использованием указанного компаратора с помощью двоичного поиска.
Принимает на вход массив фильмов, его размер, указатель на индекс (для возврата), указатель на структуру
фильма для поиска, указатель на
найденный фильм и указатель на функцию компаратора
*/
static void fa_bin_search_place_by_given(struct film_t *pfilms, size_t n, size_t *ind, struct film_t *to_search, cmp_film_t cmp)
{
    size_t l = 0, r = n, mid = (l + r) / 2;

    assert(n > 0 || n < N_MAX);

    while (r - l > 0)
    {
        if (cmp(&pfilms[mid], to_search) <= 0)
            l = mid + 1;
        else
            r = mid;
        mid = (l + r) / 2;
    }
    *ind = l;
}


/*
Функция вставляет элемент в массив фильмов по индексу.
Принимает на вход массив фильмов, size_t указатель на его длину, вставляемый фильм, size_t индекс
*/
void fa_insert(struct film_t *pfilms, size_t *n, const struct film_t *in_film, size_t ind)
{
    // Допущение: в функцию передаётся индекс не больший чем длина массива
    assert(ind <= *n);

    for (size_t i = *n; i > ind; i--)
        pfilms[i] = pfilms[i - 1];
    pfilms[ind] = *in_film;
    *n += 1;
}


/*
Функция считывает массив структур фильмов из файла (каждое поле с новой строки) с сортировкой с
использованием указанного компаратора.
Принимает на вход файловую переменную, массив фильмов, максимально допустимое кол-во фильмов, указатель на кол-во фильмов и указатель на функцию компаратора
*/
int fa_read_with_sort_by_given(FILE *f, struct film_t *pfilms, size_t n_max, size_t *n, cmp_film_t cmp)
{
    int rc = OK;
    size_t j = 0;
    *n = 0;
    struct film_t buf;
    while ((rc = film_read(f, &buf)) == OK && *n < n_max)
    {
        fa_bin_search_place_by_given(pfilms, *n, &j, &buf, cmp);
        fa_insert(pfilms, n, &buf, j);
    }

    if (*n == 0 && feof(f))
        return ERR_RANGE;
    if (!feof(f) && rc != OK)
        return rc;
    if (!feof(f) && rc == OK)
        return ERR_RANGE;
    return OK;
}


/*
Функция выводит в файл массив фильмов (каждое поле в новой строке).
Принимает на вход файловую переменную, массив фильмов и его длину
*/
int fa_print(FILE *f, const struct film_t *pfilms, size_t n)
{
    int rc;

    for (size_t i = 0; i < n; i++)
        if ((rc = film_print(f, &pfilms[i])) != OK)
            return rc;
    return OK;
}


/*
Функция находит фильм с использованием указанного компаратора с помощью двоичного поиска.
Принимает на вход массив фильмов, его размер, указатель на структуру фильма для поиска, указатель на
найденный фильм и указатель на функцию компаратора
*/
struct film_t *fa_bin_search_by_given(struct film_t *pfilms, size_t n, struct film_t *to_search, cmp_film_t cmp)
{
    size_t l = 0, r = n - 1, mid = (l + r) / 2;

    assert(n > 0 || n < N_MAX);

    while (r - l > 0)
    {
        if (cmp(&pfilms[mid], to_search) < 0)
            l = mid + 1;
        else
            r = mid;
        mid = (l + r) / 2;
    }
    if (cmp(&pfilms[mid], to_search) == 0)
        return &pfilms[l];
    else
        return NULL;
}
