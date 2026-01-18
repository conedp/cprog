#include "my_string.h"
#include <stdbool.h>

char *my_strpbrk(const char *s1, const char *s2)
{
    for (const char *psin = s1; *psin; psin++)
        for (const char *psfor = s2; *psfor; psfor++)
            if (*psin == *psfor)
                return (char*) psin;
    return NULL;
}


size_t my_strspn(const char *s1, const char *s2)
{
    size_t len = 0;
    bool in_from_s2_part = true;
    for (const char *psin = s1; *psin && in_from_s2_part; psin++)
    {
        bool curr_is_from_s2 = false;
        for (const char *psfor = s2; *psfor && !curr_is_from_s2; psfor++)
            if (*psin == *psfor)
                curr_is_from_s2 = true;
        if (curr_is_from_s2)
            len += 1;
        else
            in_from_s2_part = false;
    }
    return len;
}


size_t my_strcspn(const char *s1, const char *s2)
{
    size_t len = 0;
    bool not_in_from_s2_part = true;
    for (const char *psin = s1; *psin && not_in_from_s2_part; psin++)
    {
        bool not_curr_is_from_s2 = true;
        for (const char *psfor = s2; *psfor && not_curr_is_from_s2; psfor++)
            if (*psin == *psfor)
                not_curr_is_from_s2 = false;
        if (not_curr_is_from_s2)
            len += 1;
        else
            not_in_from_s2_part = false;
    }
    return len;
}


char *my_strchr(const char *s, int c)
{
    const char *psin = s;
    while (*psin)
    {
        if (*psin == c)
            return (char*) psin;
        psin++;
    }
    if (c == *psin)
        return (char*) psin;
    else
        return NULL;
}


char *my_strrchr(const char *s, int c)
{
    const char *pout = NULL;
    const char *psin = s;
    while (*psin)
    {
        if (*psin == c)
            pout = psin;
        psin++;
    }
    if (c == *psin)
        pout = psin;
    return (char*) pout;
}
