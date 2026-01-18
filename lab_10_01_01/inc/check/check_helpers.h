#ifndef CHECK_HELPERS__
#define CHECK_HELPERS__

#include "node.h"

int compare_lists(node_t *list1, node_t *list2, int (*comparator)(const void*, const void*));

int int_comparator(const void *a, const void *b);

int char_comparator(const void *a, const void *b);

#endif
