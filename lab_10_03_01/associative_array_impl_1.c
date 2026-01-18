#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "associative_array.h"
#include "dynamic_array.h"


struct assoc_array_type
{
    darray_t darr;
};


static assoc_array_error_t throw_error(int rc)
{
    if (rc == DARRAY_OK)
        return ASSOC_ARRAY_OK;
    else if (rc == DARRAY_INVALID_PARAM)
        return ASSOC_ARRAY_INVALID_PARAM;
    else if (rc == DARRAY_MEM)
        return ASSOC_ARRAY_MEM;
    else if (rc == DARRAY_NOT_FOUND)
        return ASSOC_ARRAY_NOT_FOUND;
    else
        return ASSOC_ARRAY_KEY_EXISTS;
}


assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (!arr)
        return NULL;
    arr->darr = dyn_array_create();
    if (!arr->darr)
    {
        free(arr);
        return NULL;
    }
    return arr;
}


void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr)
        return;
    if (!(*arr))
        return;
    dyn_array_destroy((*arr)->darr);
    free(*arr);
    *arr = NULL;
}


assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;
    return throw_error(dyn_array_insert(arr->darr, key, num));
}


assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;
    return throw_error(dyn_array_find(arr->darr, key, num));
}


assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;
    return throw_error(dyn_array_remove(arr->darr, key));
}


assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;
    return throw_error(dyn_array_clear(arr->darr));
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !arr->darr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->darr->size; i++)
        action(arr->darr->pairs[i].key, &(arr->darr->pairs[i].value), param);

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !arr->darr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->darr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    size_t min_index = 0;
    for (size_t i = 1; i < arr->darr->size; ++i)
    {
        if (strcmp(arr->darr->pairs[i].key, arr->darr->pairs[min_index].key) < 0)
            min_index = i;
    }

    *num = &(arr->darr->pairs[min_index].value);

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !arr->darr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->darr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    size_t max_index = 0;
    for (size_t i = 1; i < arr->darr->size; ++i)
    {
        if (strcmp(arr->darr->pairs[i].key, arr->darr->pairs[max_index].key) > 0)
            max_index = i;
    }

    *num = &(arr->darr->pairs[max_index].value);

    return ASSOC_ARRAY_OK;
}
