#ifndef LIST__
#define LIST__

#include "node.h"
#include "data_struct.h"

#include <stddef.h>

node_t *fill_list_from_array(void *arr, size_t size, size_t n);

void free_list(node_t *head);

node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*));

void remove_duplicates(node_t **head, int (*comparator)(const void*, const void*));

void insert(node_t **head, node_t *elem, node_t *before);

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif
