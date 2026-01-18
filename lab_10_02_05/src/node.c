#include <stdlib.h>

#include "node.h"


/*
Функция выделяет память под узел и записывает в него PART_LEN символов из строки str, начиная с ind.
Принимает на вход строку s и size_t индекс первого элемента подстроки.
*/
node_t *create_node(char *s, size_t ind)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        return NULL;
    size_t i = 0;
    while (i < PART_LEN && s[ind + i] != 0)
    {
        tmp->s[i] = s[ind + i];
        i++;
    }
    if (s[ind + i] == 0)
        tmp->s[i] = s[ind + i];
    tmp->next = NULL;
    return tmp;
}


/*
Функция удяляет узел списка.
Принимает на вход указатель на узел
*/
void node_free(node_t *node)
{
    free(node);
}
