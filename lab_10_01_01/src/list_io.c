#include "list_io.h"
#include "data_io.h"


void print_certain(node_t *head, int (*is_certain)(const void *))
{
    node_t *curr = head;
    while (curr)
    {
        if (is_certain(curr->data))
            print_storage_item(curr->data);
        curr = curr->next;
    }
}
