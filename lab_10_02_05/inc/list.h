#ifndef LIST__
#define LIST__

#include "node.h"

#include <stddef.h>

node_t *fill_list_from_string(char *str);

void free_list(node_t *head);

int concatenate(node_t **head_1, node_t *head_2);

int delete_excess_spaces(node_t *head);

int find_substring(node_t *head, char *substr, size_t *pos);

void print_str(node_t *head);

#endif
