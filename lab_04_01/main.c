#include "testing.h"
#include "my_string.h"
#include <stdio.h>

int main(void)
{
    unsigned failed_all = test_all();
    printf("%u\n", failed_all);
    return failed_all;
}
