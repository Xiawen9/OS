#include <String.h>
#include <Types.h>
#include <Character.h>
#include "stdlib.h"

extern C long strtol(const char *nptr, char **endptr, int base)
{
    String s = nptr;
    Number::Base b = Number::Dec;
    
    switch (base)
    {
        case 10: b = Number::Dec; break;
        case 16: b = Number::Hex; break;
    }

    if (*nptr && *nptr == '-')
        nptr++;

    if (*nptr && *nptr == '0' && *(nptr+1) && *(nptr+1) == 'x')
        nptr += 2;

    while (Character::isDigit(*nptr))
        nptr++;

    *endptr = (char *) nptr;

    return s.toLong(b);
}
