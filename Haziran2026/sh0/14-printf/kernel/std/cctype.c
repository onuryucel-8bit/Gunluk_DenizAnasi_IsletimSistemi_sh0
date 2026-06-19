#include "cctype.h"

bool isalpha(uint8_t ch)
{
    if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
    {
        return true;
    }

    return false;
}