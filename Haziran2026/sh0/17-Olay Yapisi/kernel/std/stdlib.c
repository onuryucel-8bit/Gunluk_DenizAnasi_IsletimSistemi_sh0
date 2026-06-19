#include "stdlib.h"

static uint32_t heapPtr = (uint32_t)0x00F00000;

void* malloc(size_t size)
{
    void* retPtr = (void*)heapPtr;
    heapPtr += size;

    return (void*)retPtr;
}

//TODO bitwise check?
int abs(int a)
{
    if(a < 0)
    {
        a *= -1;
    }

    return a;
}