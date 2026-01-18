#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

#define ERR_OK 0
#define ERR_IO 1

/*
Выводит передаваемое в него uint32_t в бинарной форме
*/
void bin_print(uint32_t n)
{
    unsigned int nbits = sizeof(n) * CHAR_BIT;
    uint32_t mask = (uint32_t) 1 << (nbits - 1);
    
    for (unsigned int i = 0; i < nbits; i++)
    {
        if (n & mask)
            printf("1");
        else
            printf("0");
        mask >>= 1;
    }
    printf("\n");
}


/*
Выполняет перестановку соседних чётных и нечётных битов (0 и 1, 2 и 3)
*/
uint32_t odd_even_permutation(uint32_t n)
{
    uint32_t o = 0, b1, b2;
    unsigned int nbits = sizeof(o) * CHAR_BIT;
    uint32_t mask = (uint32_t) 1 << (nbits - 1);
    
    for (unsigned int i = 0; i < nbits; i += 2)
    {
        b1 = n & mask;
        b1 >>= 1;
        mask >>= 1;
        b2 = n & mask;
        b2 <<= 1;
        mask >>= 1;
        o |= b1;
        o |= b2;
    }
    return o;
}


int main(void)
{
    uint32_t n, ans;
    
    printf("Input n: ");
    if (scanf("%" SCNu32 "", &n) != 1)
    {
        printf("Error: wrong input");
        return ERR_IO;
    }
    
    ans = odd_even_permutation(n);

    printf("Result: ");
    bin_print(ans);
    return ERR_OK;
}

