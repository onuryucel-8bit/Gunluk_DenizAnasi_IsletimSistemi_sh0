#include "string.h"

size_t strlen(const char* str)
{
    size_t length = 0;
    while(str[length])
    {
        length++;        
    }
    return length;
}


void* memset(void *ptr, int x, size_t n)
{
    uint16_t* p = (uint16_t*) ptr;
    
    for (size_t i = 0; i < n; i++)
    {
        p[i] = (uint16_t)x;
    }

    return ptr;
}