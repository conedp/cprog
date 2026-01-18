#include "constants.h"
#include "errors.h"
#include "io.h"
#include "get_answer.h"


int main(void)
{
    char str[STR_LEN];
    int rc;
    if ((rc = get_line(str, sizeof(str))) != OK)
        return rc;
    
    print_answer(is_a_phone_number(str));
}
