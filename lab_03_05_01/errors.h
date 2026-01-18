#ifndef ERRORS__
#define ERRORS__

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO_SUITABLE 3

#include <stdio.h>

void print_error(int rc);

#endif
