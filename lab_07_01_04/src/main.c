#include "errors.h"
#include "darray_ioa.h"
#include "darray_op.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARGC_MIN 3
#define ARGC_MAX 4


int main(int argc, char **argv)
{
    int rc = OK;
    int *pbeg_in, *pend_in;
    int *pbeg_f = NULL, *pend_f = NULL;
    bool key_needed = false;

    // Проверка на корректность количества аргументов
    if (argc < ARGC_MIN || argc > ARGC_MAX)
    {
        return ERR_ARGS;
    }

    // Чтение массива
    rc = da_fread(&pbeg_in, &pend_in, argv[1]);
    if (rc != OK)
        return rc;

    if (argc == 4)
    {
        if (strcmp("f", argv[3]) == 0)
        {
            key_needed = true;
        }
        else
        {
            rc = ERR_ARGS;
            free(pbeg_in);
        }
    }

    if (rc == OK)
    {
        if (key_needed)
        {
            rc = key(pbeg_in, pend_in, &pbeg_f, &pend_f);
            free(pbeg_in);
        }
        else
        {
            pbeg_f = pbeg_in;
            pend_f = pend_in;
        }

        if (rc == OK)
        {
            // Сортировка
            size_t len = (pend_f - pbeg_f);
            mysort(pbeg_f, len, sizeof(int), cmp_uni_int);

            // Запись массива в файл
            rc = da_fprint_ex(pbeg_f, pend_f, argv[2]);
        }
    }

    free(pbeg_f);

    return rc;
}
