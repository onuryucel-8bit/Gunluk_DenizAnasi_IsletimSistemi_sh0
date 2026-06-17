#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);

// ptr ==> Starting address of memory to be filled
// x   ==> Value to be filled
// n   ==> Number of bytes to be filled starting 
//         from ptr to be filled
void* memset(void *ptr, int x, size_t n);

int strcmp (const char* str1, const char* str2 );

#endif