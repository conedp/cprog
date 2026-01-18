#ifndef NODE__
#define NODE__

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

node_t *create_node(void *data);

void *node_free(node_t *node);

#endif
