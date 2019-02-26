#ifndef __LIBALLOC_PAGEALLOCATOR_H
#define __LIBALLOC_PAGEALLOCATOR_H

#include <System.h>
#include <Types.h>
#include "Allocator.h"

#define PAGEALLOC_MINIMUM (PAGESIZE * 2)

class PageAllocator : public Allocator
{
  public:
    PageAllocator(Address start, Size size);
    PageAllocator(PageAllocator *p);
    Address base();
    virtual Size size();
    virtual Size available();
    virtual Result allocate(Size *size, Address *addr, Size align = ZERO);
    virtual Result release(Address addr);

  private:
    Address m_base;
    Size m_size;
    Size m_allocated;
};

#endif /* __LIBALLOC_PAGEALLOCATOR_H */
