#include "data_struct.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/*
Функция сравнивает структурры данных по имени.
Принимает на вход указатели на структуры данных.
*/
int cmp_item_name(const void *l, const void *r)
{
    assert(l);
    assert(r);

    const storage_item_t *pl = l;
    const storage_item_t *pr = r;

    return strcmp(pl->name, pr->name);
}


/*
Функция сравнивает структурры данных по количество дней n_days.
Принимает на вход указатели на структуры данных.
*/
int cmp_item_days_reverse(const void *l, const void *r)
{
    assert(l);
    assert(r);

    const storage_item_t *pl = l;
    const storage_item_t *pr = r;

    return pr->n_days - pl->n_days;
}


/*
Фукнция проверяет пролежал ли товар на складе больше 365 дней.
Принимает на вход указатель на void.
*/
int is_outdated(const void *data)
{
    const int date_verge = 365;
    const storage_item_t *pdata = data;
    if (pdata->n_days > date_verge)
        return 1;
    else
        return 0;
}


/*
Функция выводит на экран информацию об одном товаре.
Принимает на вход указатель на структуру storage_item_t.
*/
void print_storage_item(const storage_item_t *item)
{
    printf("%s\n", item->name);
    printf("%d\n", item->cost);
    printf("%d\n", item->n_days);
}


/*
Функция освобождает память из-под массива данных.
Принимает на вход массив данных и его длину.
*/
void storage_free(storage_item_t *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(arr[i].name);
    free(arr);
}
