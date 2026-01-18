#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define ACCURACY 1e-8

int main(void) 
{
    double v_0, a, t;
    double s;
    
    printf("Input start velocity, acceleration, time: ");
    if (scanf("%lf %lf %lf", &v_0, &a, &t) != 3)
        return ERR_IO;
    
    if (t < 0)
        return ERR_RANGE;
    
    if (fabs(t) < ACCURACY)
        s = 0.0;
    else
        s = v_0 * t + a * t * t / 2;
    
    printf("Movement: %lf\n", s);
    return ERR_OK;
}
