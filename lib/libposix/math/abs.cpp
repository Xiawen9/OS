#include "limits.h"
#include "math.h"

int abs(int number)
{
    int const mask = number >> (sizeof(int) * CHAR_BIT - 1);
    return (number + mask) ^ mask;
}
