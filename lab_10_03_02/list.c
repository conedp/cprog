#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


list_t assoc_list_create(void)
{
    list_t arr = malloc(sizeof(struct list_type));
    if (!arr)
        return NULL;

    arr->head = NULL;
    return arr;
}


void assoc_list_destroy(list_t arr)
{
    if (!arr)
        return;

    assoc_list_clear(arr);
    free(arr);
}


int assoc_list_insert(list_t arr, const char *key, int num)
{
    if (!arr || !key)
        return LIST_INVALID_PARAM;
    if (key[0] == '\0')
        return LIST_INVALID_PARAM;

    key_value_node_t *current = arr->head;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
            return LIST_KEY_EXISTS;
        current = current->next;
    }

    key_value_node_t *new_node = malloc(sizeof(key_value_node_t));
    if (new_node == NULL)
        return LIST_MEM;

    char *key_copy = strdup(key);
    if (key_copy == NULL)
    {
        free(new_node);
        return LIST_MEM;
    }

    new_node->key = key_copy;
    new_node->value = num;
    new_node->next = arr->head;
    arr->head = new_node;

    return LIST_OK;
}


int assoc_list_find(const list_t arr, const char *key, int **num)
{
    if (!arr || !key || !num)
        return LIST_INVALID_PARAM;
    if (key[0] == '\0')
        return LIST_INVALID_PARAM;

    key_value_node_t *current = arr->head;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            *num = &(current->value);
            return LIST_OK;
        }
        current = current->next;
    }

    return LIST_NOT_FOUND;
}

int assoc_list_remove(list_t arr, const char *key)
{
    if (!arr || !key)
        return LIST_INVALID_PARAM;
    if (key[0] == '\0')
        return LIST_INVALID_PARAM;

    key_value_node_t *current = arr->head;
    key_value_node_t *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
                arr->head = current->next;
            else
                prev->next = current->next;

            free(current->key);
            free(current);
            return LIST_OK;
        }
        prev = current;
        current = current->next;
    }

    return LIST_NOT_FOUND;
}


int assoc_list_clear(list_t arr)
{
    if (!arr)
        return LIST_INVALID_PARAM;

    key_value_node_t *current = arr->head;
    key_value_node_t *next_node;

    while (current != NULL)
    {
        next_node = current->next;
        free(current->key);
        free(current);
        current = next_node;
    }

    arr->head = NULL;

    return LIST_OK;
}
