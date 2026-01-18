#include <stdio.h>
#include <stddef.h>
#include <limits.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

/*
Возводит a в степень n
*/
int power(int a, int n)
{
    int z = a, ans = 1;
    int mask = 1;

    for (size_t i = 0; mask <= n && i < sizeof(a)*CHAR_BIT; i++)
    {
        if (mask & n)
        {
            ans *= z;
            z *= z;   
        }
        else
            z *= z;
        mask <<= 1;
    }
    return ans;
}



int main(void) 
{
    int a, ans, n;
    
    printf("Input a and n: ");
    if (scanf("%d %d", &a, &n) != 2)
    {
        return ERR_IO;
    }
    if (n <= 0)
        return ERR_RANGE;
    
    ans = power(a, n);
    
    printf("a in powet n = %d\n", ans);
}
