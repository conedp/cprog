#include <stddef.h>
#include <string.h>

#include "list.h"


int compare_lists(node_t *head1, node_t *head2)
{
    node_t *current1 = head1;
    node_t *current2 = head2;

    while (current1 != NULL && current2 != NULL)
    {
        for (int i = 0; i < PART_LEN; ++i)
        {
            char char1 = current1->s[i];
            char char2 = current2->s[i];

            if (char1 != char2)
            {
                return 1;
            }

            if (char1 == '\0')
            {
                break;
            }
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    if (current1 != NULL || current2 != NULL)
    {
        return 1;
    }

    return 0;
}
