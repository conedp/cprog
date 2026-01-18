#include <stdio.h>
#include <math.h>

#define PI 3.141592
#define HALF_CIRCLE 180

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int main(void)
{
    double a, b, ph;
    double area;
    
    printf("Input a, b, ph: ");
    
    if (scanf("%lf%lf%lf", &a, &b, &ph) != 3)
    {
        return ERR_IO;
    }
    if (a <= 0 || b <= 0) 
    {
        return ERR_RANGE;
    }
    if (!(ph > 0 && ph < HALF_CIRCLE)) 
    {
        return ERR_RANGE;
    }
    
    area = (a * b * sin((ph * PI) / HALF_CIRCLE)) / 2;
    
    printf("Area of a given triangle = %lf\n", area);
    return ERR_OK;
}
