#include "check_helpers.h"
#include <stddef.h>


int compare_lists(node_t *list1, node_t *list2, int (*comparator)(const void*, const void*))
{
    while (list1 != NULL && list2 != NULL)
    {
        if (comparator(list1->data, list2->data) != 0)
        {
            return 0;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    if (list1 != NULL || list2 != NULL)
    {
        return 0;
    }
    return 1;
}

int int_comparator(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int char_comparator(const void *a, const void *b)
{
    return (*(char*)a - *(char*)b);
}
