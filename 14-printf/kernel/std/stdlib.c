#include "stdlib.h"

//TODO bitwise check?
int abs(int a)
{
    if(a < 0)
    {
        a *= -1;
    }

    return a;
}