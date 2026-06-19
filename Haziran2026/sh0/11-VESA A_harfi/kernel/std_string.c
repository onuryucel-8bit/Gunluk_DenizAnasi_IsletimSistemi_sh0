#include "std_string.h"

size_t strlen(const char* str)
{
    const char* end = str;
    while (*end != '\0')
    {
        ++end;
    }
    return end - str;
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