#include <stdlib.h>
#include <string.h>
#include "darray_ioa.h"
#include "errors.h"

/*
Функция выделяет память для динамического массива.
Принимает на вход size_t размер массива, size_t размер элемента в байтах и двойной указатель на начало массива
*/
int *da_alloc(size_t n, size_t size)
{
    int *tmp;
    if (size == 0 || n == 0)
        return NULL;
    tmp = malloc(n * size);
    if (!tmp)
        return NULL;
    return tmp;
}


/*
Функция считает количество целых чисел, записанных в файле.
Приниамет на вход файловую переменную, и указатель на size_t количество чисел
*/
static int f_count_ints(FILE *f, size_t *n)
{
    rewind(f);
    int curr, rc = OK;

    while (fscanf(f, "%d", &curr) == 1)
        *n += 1;
    if (!feof(f))
        rc = ERR_DATA;
    return rc;
}


/*
Функция считаетет из файла массив целых чисел.
Приниамет на вход файловую переменную, указатель на начало массива, указатель за конец массива
*/
static int f_read_array(FILE *f, int *pbeg, int *pend)
{
    rewind(f);
    int rc = OK;
    for (int *pcur = pbeg; rc == OK && pcur < pend; pcur += 1)
    {
        if (fscanf(f, "%d", pcur) != 1)
            rc = ERR_IO;
    }
    return rc;
}


/*
Функция считывает массив неизвестной длины из файла в динамический массив.
Принимает на выход размер элемента, двойной указатель на начало массив, двойной указатель за его конец и строку - название файла.
*/
int da_fread(int **data, int **data_end, char *file_name)
{
    FILE *f = fopen(file_name, "r");
    int rc = OK;
    size_t n = 0;
    if (!f)
        return ERR_FILE_OPEN;
    rc = f_count_ints(f, &n);
    if (n == 0)
        rc = ERR_DATA;

    if (rc == OK)
    {
        *data = da_alloc(n, sizeof(int));
        if (*data)
        {
            *data_end = *data + n;
            rc = f_read_array(f, *data, *data_end);
        }
        else
            rc = ERR_MEM;
    }

    fclose(f);

    return rc;
}



/*
Функция выводит в файл массив через пробел.
Принмиает на вход указетль на начало массива, указатель за его конец и файловую переменную
*/
int da_fprint(const int *pbeg, const int *pend, FILE *f)
{
    for (const int *pcur = pbeg; pcur < pend - 1; pcur++)
    {
        if (fprintf(f, "%d ", *pcur) < 0)
            return ERR_FILE_WRITE;
    }
    fprintf(f, "%d\n", *(pend - 1));
    return OK;
}


/*
Функция выводит в файл массив через пробел.
Принмиает на вход указетль на начало массива, указатель за его конец и строку - название файла.
*/
int da_fprint_ex(const int *pbeg, const int *pend, char *file_name)
{
    int rc = OK;
    FILE *f = fopen(file_name, "w");
    if (!f)
        return ERR_FILE_OPEN;
    rc = da_fprint(pbeg, pend, f);
    fclose(f);
    return rc;
}
