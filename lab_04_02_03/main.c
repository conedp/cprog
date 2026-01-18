#include "constants.h"
#include "errors.h"
#include "io.h"
#include "get_answer.h"
#include <stdio.h>


int main(void)
{
    char str_1[STR_LEN], str_2[STR_LEN];
    char words_1[N][WORD_LEN], words_2[N][WORD_LEN];
    char words_out[M][WORD_LEN];
    size_t words_1_n, words_2_n, words_out_n;
    int rc;
    printf("Input first line: ");
    if ((rc = get_line(str_1, sizeof(str_1))) != OK)
    {
        print_error(rc);
        return rc;
    }
    printf("Input second line: ");
    if ((rc = get_line(str_2, sizeof(str_2))) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    if ((rc = parse_string(str_1, words_1, &words_1_n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    if ((rc = parse_string(str_2, words_2, &words_2_n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    form_array(words_1, words_1_n, words_2, words_2_n, words_out, &words_out_n);
    
    printf("Result: ");
    print_word_array(words_out, words_out_n);
}
