#include <stdlib.h>

#include "node.h"

node_t *create_node(void *data)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    tmp->data = data;
    tmp->next = NULL;
    return tmp;
}


/*
Функция удяляет узел списка и возвращает указатель на данные из узла.
Принимает на вход указатель на узел
*/
void *node_free(node_t *node)
{
    if (!node)
        return NULL;
    void *data_tmp = node->data;
    free(node);
    return data_tmp;
}
