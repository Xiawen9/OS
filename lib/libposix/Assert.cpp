#include <System.h>
#include <API.h>
#include <Assert.h>
#include <Macros.h>
#include <Types.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void __assertFailure(const char *fmt, ...)
{
    va_list args;
    
    /* Output assertion failure message. */
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    
    /* Terminate immediately. */
    exit(EXIT_FAILURE);
}

int __assertRead(Address addr)
{
    Memory::Range range;

    range.virt   = addr;
    range.phys   = ZERO;
    range.size   = sizeof(Address);
    range.access = Memory::User | Memory::Readable;

    return VMCtl(SELF, Access, &range);
}

int __assertWrite(Address addr)
{
    Memory::Range range;

    range.virt   = addr;
    range.phys   = ZERO;
    range.size   = sizeof(Address);
    range.access = Memory::User | Memory::Readable;

    return VMCtl(SELF, Access, &range);
}
