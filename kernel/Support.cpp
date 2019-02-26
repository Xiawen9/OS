#include <Macros.h>
#include <Assert.h>
#include "Support.h"
#include "Kernel.h"

// TODO: #warning FIX asserts plz

extern C void constructors()
{
    for (void (**ctor)() = &CTOR_LIST; *ctor; ctor++)
    {
        (*ctor)();
    }
}

extern C void destructors()
{
    for (void (**dtor)() = &DTOR_LIST; *dtor; dtor++)
    {
        (*dtor)();
    }
}

#ifdef __ASSERT__

extern C void __assertFailure(const char *fmt, ...)
{
    for (;;) ;
}

extern C int __assertRead(Address addr)
{

    if (memory && scheduler && scheduler->current())
    {
        return memory->access(scheduler->current(), addr,
                              sizeof(Address), PAGE_PRESENT|PAGE_USER);
    }
    return true;
}

extern C int __assertWrite(Address addr)
{
    if (memory && scheduler && scheduler->current())
    {
        return memory->access(scheduler->current(), addr,
                              sizeof(Address), PAGE_PRESENT|PAGE_USER|PAGE_RW);
    }
    return true;
}

#endif /* __ASSERT__ */

extern C void __cxa_pure_virtual()
{
}

extern C void __dso_handle()
{
}

extern C void __stack_chk_fail(void)
{
}

extern C int __cxa_atexit(void (*func) (void *), void * arg, void * dso_handle)
{
    return (0);
}

extern C int raise(int sig)
{
    return 0;
}
