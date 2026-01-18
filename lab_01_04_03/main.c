#include <stdio.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define BASE 10

int main(void)
{
    int n;
    int p;
    
    printf("Input three-digit integer: ");
    if (scanf("%d", &n) != 1)
        return ERR_IO;
    
    if (n < 0)
        n = -n;
    
    if (n / (BASE * BASE * BASE) != 0 || n / (BASE * BASE) == 0)
        return ERR_RANGE;
    
    p = (n / (BASE * BASE)) * ((n % (BASE * BASE)) / BASE) * (n % BASE);
    
    printf("Product of numbers = %d\n", p);
    return ERR_OK;
}
