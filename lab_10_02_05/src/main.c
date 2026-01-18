#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "errors.h"
#include "node.h"
#include "list.h"

#define OUT_LINE "out"
#define CAT_LINE "cat"
#define SPS_LINE "sps"
#define POS_LINE "pos"

enum mode_t
{
    OUT,
    CAT,
    SPS,
    POS
};


int main(void)
{
    int rc = OK;

    enum mode_t mode;
    char *mode_str = NULL;
    size_t mode_str_len = 0, n = 0;
    ssize_t getln_rc;

    if ((getln_rc = getline(&mode_str, &n, stdin)) == -1)
    {
        free(mode_str);
        return ERR_MODE;
    }
    mode_str_len = strlen(mode_str);
    if (mode_str[mode_str_len - 1] == '\n')
        mode_str[mode_str_len - 1] = 0;

    if (strcmp(OUT_LINE, mode_str) == 0)
        mode = OUT;
    else if (strcmp(CAT_LINE, mode_str) == 0)
        mode = CAT;
    else if (strcmp(SPS_LINE, mode_str) == 0)
        mode = SPS;
    else if (strcmp(POS_LINE, mode_str) == 0)
        mode = POS;
    else
    {
        free(mode_str);
        return ERR_MODE;
    }
    free(mode_str);

    node_t *list = NULL, *list_2 = NULL;
    char *str = NULL, *str_2 = NULL;
    size_t str_len = 0, str_2_len = 0, position;

    if ((getln_rc = getline(&str, &n, stdin)) != -1)
    {
        str_len = strlen(str);
        if (str[str_len - 1] == '\n')
        {
            str[str_len - 1] = 0;
            str_len--;
        }
        if (str_len != 0)
        {
            list = fill_list_from_string(str);
            if (list)
            {
                if (mode == OUT)
                {
                    print_str(list);
                }
                else if (mode == CAT)
                {
                    if ((getln_rc = getline(&str_2, &n, stdin)) != -1)
                    {
                        str_2_len = strlen(str_2);
                        if (str_2[str_2_len - 1] == '\n')
                        {
                            str_2[str_2_len - 1] = 0;
                            str_2_len--;
                        }
                        if (str_2_len != 0)
                        {
                            list_2 = fill_list_from_string(str_2);
                            if (list_2)
                            {
                                rc = concatenate(&list, list_2);
                                if (rc == OK)
                                    print_str(list);
                                else
                                {
                                    free(str);
                                    free(str_2);
                                    free_list(list);
                                    free_list(list_2);
                                }
                            }
                            else
                            {
                                free(str);
                                free(str_2);
                                free_list(list);
                                rc = ERR_MEM;
                            }
                        }
                        else
                        {
                            free(str);
                            free(str_2);
                            free_list(list);
                            rc = ERR_RANGE;
                        }
                    }
                    else
                    {
                        free(str);
                        free(str_2);
                        free_list(list);
                        rc = ERR_MEM;
                    }
                }
                else if (mode == SPS)
                {
                    rc = delete_excess_spaces(list);
                    if (rc == OK)
                        print_str(list);
                    else
                    {
                        free(str);
                        free_list(list);
                    }
                }
                else if (mode == POS)
                {
                    if ((getln_rc = getline(&str_2, &n, stdin)) != -1)
                    {
                        str_2_len = strlen(str_2);
                        if (str_2[str_2_len - 1] == '\n')
                        {
                            str_2[str_2_len - 1] = 0;
                            str_2_len--;
                        }
                        if (str_2_len != 0)
                        {
                            rc = find_substring(list, str_2, &position);
                            if (rc == NOT_FOUND)
                            {
                                printf("-1\n");
                                rc = OK;
                            }
                            else
                            {
                                if (rc == OK)
                                    printf("%zu\n", position);
                                else
                                {
                                    free(str);
                                    free(str_2);
                                    free_list(list);
                                }
                            }
                        }
                        else
                        {
                            free(str);
                            free(str_2);
                            free_list(list);
                            rc = ERR_RANGE;
                        }
                    }
                    else
                    {
                        free(str);
                        free(str_2);
                        free_list(list);
                        rc = ERR_MEM;
                    }
                }
            }
            else
            {
                free(str);
                rc = ERR_MEM;
            }
        }
        else
        {
            free(str);
            rc = ERR_RANGE;
        }
    }
    else
    {
        free(str);
        rc = ERR_MEM;
    }

    if (rc == OK)
    {
        free(str);
        free(str_2);
        free_list(list);
        free_list(list_2);
    }

    return rc;
}

