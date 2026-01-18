#ifndef ERRORS__
#define ERRORS__

#include <stdio.h>


#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_EMPTY_MATRIX 3


void print_error(int rc);

#endif
