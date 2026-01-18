#ifndef ERRORS__
#define ERRORS__

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_BUF_TOO_SMALL 3
#define ERR_TOO_MUCH_WORDS 4
#define ERR_NOT_ENOUGH_WORDS 5

void print_error(int rc);

#endif
