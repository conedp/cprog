#define _POSIX_C_SOURCE 200809L

#include "data_io.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>


storage_item_t *item_array_alloc(size_t n)
{
    storage_item_t *tmp = malloc(n * sizeof(storage_item_t));
    if (!tmp)
        return NULL;
    return tmp;
}


int data_input(FILE *f, size_t n, storage_item_t *arr)
{
    char *name_str = NULL, *tmp;
    ssize_t name_len;
    size_t len = 0;
    int cost, n_days;
    for (size_t i = 0; i < n; i++)
    {
        name_len = getline(&name_str, &len, f);
        if (name_len == -1)
        {
            free(name_str);
            return ERR_MEM;
        }
        // > 1 чтобы пустая (содержащая только \n) строка считалась ошибкой
        else if (name_len == 0 || name_len == 1)
        {
            free(name_str);
            return ERR_DATA;
        }
        if (name_str[name_len - 1] == '\n')
            name_str[name_len - 1] = '\0';
        else
        {
            free(name_str);
            return ERR_DATA;
        }
        if (fscanf(f, "%d\n", &cost) != 1)
        {
            free(name_str);
            return ERR_DATA;
        }
        if (cost < 0)
        {
            free(name_str);
            return ERR_RANGE;
        }
        if (fscanf(f, "%d\n", &n_days) != 1)
        {
            free(name_str);
            return ERR_DATA;
        }
        if (n_days < 0)
        {
            free(name_str);
            return ERR_RANGE;
        }

        tmp = strdup(name_str);
        if (!tmp)
        {
            free(name_str);
            return ERR_MEM;
        }
        arr[i].name = tmp;
        arr[i].cost = cost;
        arr[i].n_days = n_days;
    }
    if (!feof(f))
    {
        free(name_str);
        return ERR_DATA;
    }
    free(name_str);
    return OK;
}


int data_read_ex(char *file_name, size_t *n, storage_item_t **arr)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return ERR_FILE_OPEN;

    size_t data_n;
    char c;
    int rc;
    if (fscanf(f, "%zu%c", &data_n, &c) != 2)
    {
        fclose(f);
        return ERR_DATA;
    }
    if (data_n == 0)
    {
        fclose(f);
        return ERR_RANGE;
    }
    storage_item_t *tmp = item_array_alloc(data_n);
    if (tmp)
    {
        rc = data_input(f, data_n, tmp);
        if (rc == OK)
        {
            *arr = tmp;
            *n = data_n;
        }
        else
            free(tmp);
    }
    else
        rc = ERR_MEM;

    fclose(f);
    return rc;
}
