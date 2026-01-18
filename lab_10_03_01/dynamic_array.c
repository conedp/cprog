#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"


darray_t dyn_array_create(void)
{
    darray_t arr = malloc(sizeof(struct dynamic_array_type));
    if (!arr)
    {
        return NULL;
    }

    arr->capacity = INIT_CAPACITY;
    arr->size = 0;
    arr->pairs = malloc(arr->capacity * sizeof(key_value_pair_t));
    if (!arr->pairs)
    {
        free(arr);
        return NULL;
    }
    return arr;
}


void dyn_array_destroy(darray_t arr)
{
    if (!arr)
        return;

    if (arr->pairs)
        dyn_array_clear(arr);
    free(arr->pairs);
    free(arr);
}


int resize_array(darray_t arr)
{
    if (!arr)
        return DARRAY_INVALID_PARAM;

    size_t new_capacity = arr->capacity * RESIZE;

    key_value_pair_t *new_pairs = realloc(arr->pairs, sizeof(key_value_pair_t) * new_capacity);
    if (!new_pairs)
        return DARRAY_MEM;

    arr->pairs = new_pairs;
    arr->capacity = new_capacity;
    return DARRAY_OK;
}


int dyn_array_insert(darray_t arr, const char *key, int num)
{
    if (!arr || !key)
        return DARRAY_INVALID_PARAM;
    if (key[0] == '\0')
        return DARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
    {
        if (strcmp(arr->pairs[i].key, key) == 0)
            return DARRAY_KEY_EXISTS;
    }

    if (arr->size >= arr->capacity)
    {
        int rc = resize_array(arr);
        if (rc != DARRAY_OK)
            return rc;
    }

    char *key_copy = strdup(key);
    if (!key_copy)
        return DARRAY_MEM;

    arr->pairs[arr->size].key = key_copy;
    arr->pairs[arr->size].value = num;
    arr->size += 1;

    return DARRAY_OK;
}


int dyn_array_find(const darray_t arr, const char *key, int **num)
{
    if (!arr || !key || !num)
        return DARRAY_INVALID_PARAM;
    if (key[0] == '\0')
        return DARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
    {
        if (strcmp(arr->pairs[i].key, key) == 0)
        {
            *num = &(arr->pairs[i].value);
            return DARRAY_OK;
        }
    }

    return DARRAY_NOT_FOUND;
}


int dyn_array_remove(darray_t arr, const char *key)
{
    if (!arr || !key)
        return DARRAY_INVALID_PARAM;
    if (key[0] == '\0')
        return DARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
    {
        if (strcmp(arr->pairs[i].key, key) == 0)
        {
            free(arr->pairs[i].key);
            for (size_t j = i; j < arr->size - 1; j++)
                arr->pairs[j] = arr->pairs[j + 1];
            arr->size--;
            return DARRAY_OK;
        }
    }

    return DARRAY_NOT_FOUND;
}


int dyn_array_clear(darray_t arr)
{
    if (!arr)
        return DARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
        free(arr->pairs[i].key);
    arr->size = 0;
    return DARRAY_OK;
}
