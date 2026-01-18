#ifndef LIST_IO__
#define LIST_IO__

#include "node.h"

void print_certain(node_t *head, int (*is_certain)(const void *));

#endif
