#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "associative_array.h"
#include "list.h"

struct assoc_array_type
{
    list_t list;
};


static assoc_array_error_t throw_error(int rc)
{
    if (rc == LIST_OK)
        return ASSOC_ARRAY_OK;
    else if (rc == LIST_INVALID_PARAM)
        return ASSOC_ARRAY_INVALID_PARAM;
    else if (rc == LIST_MEM)
        return ASSOC_ARRAY_MEM;
    else if (rc == LIST_NOT_FOUND)
        return ASSOC_ARRAY_NOT_FOUND;
    else
        return ASSOC_ARRAY_KEY_EXISTS;
}


assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (!arr)
        return NULL;
    arr->list = assoc_list_create();
    if (!arr->list)
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
    assoc_list_destroy((*arr)->list);
    free(*arr);
    *arr = NULL;
}


assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;
    return throw_error(assoc_list_insert(arr->list, key, num));
}


assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;
    return throw_error(assoc_list_find(arr->list, key, num));
}


assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;
    return throw_error(assoc_list_remove(arr->list, key));
}


assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;
    return throw_error(assoc_list_clear(arr->list));
}


assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !arr->list || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    key_value_node_t *current = arr->list->head;
    while (current != NULL)
    {
        action(current->key, &(current->value), param);
        current = current->next;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !arr->list || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->list->head == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    key_value_node_t *min_node = arr->list->head;
    key_value_node_t *current = arr->list->head->next;

    while (current != NULL)
    {
        if (strcmp(current->key, min_node->key) < 0)
            min_node = current;

        current = current->next;
    }

    *num = &(min_node->value);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !arr->list || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->list->head == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    key_value_node_t *max_node = arr->list->head;
    key_value_node_t *current = arr->list->head->next;

    while (current != NULL)
    {
        if (strcmp(current->key, max_node->key) > 0)
            max_node = current;

        current = current->next;
    }

    *num = &(max_node->value);

    return ASSOC_ARRAY_OK;
}







