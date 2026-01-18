#ifndef NODE__
#define NODE__

#define PART_LEN 4

#include <stddef.h>

typedef struct node
{
    char s[PART_LEN];
    struct node *next;
} node_t;

node_t *create_node(char *s, size_t ind);

void node_free(node_t *node);

#endif
