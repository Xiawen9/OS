#include "string.h"

char * strncat(char *dest, const char *src, size_t n)
{
    char *s = dest;

    while (*s)
	s++;

    strncpy(s, src, n);
    return dest;
}
