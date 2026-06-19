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

//https://github.com/zerovm/glibc/blob/master/string/strcmp.c
//TODO unsigned reg_char c1, c2; ney? reg_char???

int strcmp (const char* str1, const char* str2 )
{
    int i = 0;
    while (str1[i] == str2[i])
    {
        if(str1[i] == '\0')
        {
            return 0;
        }
        i++;
    }
    
    return str1[i] - str2[i];    
}