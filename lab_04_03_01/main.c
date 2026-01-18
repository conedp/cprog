#include "constants.h"
#include "errors.h"
#include "io.h"
#include "get_answer.h"
#include <stdio.h>

int main(void)
{
    char str_in[STR_LEN], str_out[STR_LEN] = "";
    char words[N][WORD_LEN];
    size_t words_n;
    int rc;
    printf("Input line: ");
    if ((rc = get_line(str_in, sizeof(str_in))) != OK)
    {
        print_error(rc);
        return rc;
    }
    if (!*str_in)
    {
        print_error(ERR_NOT_ENOUGH_WORDS);
        return ERR_NOT_ENOUGH_WORDS;
    }
    if ((rc = parse_string(str_in, words, &words_n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    if ((rc = fill_string(str_out, words, words_n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    printf("Result: %s\n", str_out);
}
