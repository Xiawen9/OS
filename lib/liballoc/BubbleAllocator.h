#ifndef __LIBALLOC_BUBBLEALLOCATOR_H
#define __LIBALLOC_BUBBLEALLOCATOR_H

#include <Types.h>
#include "Allocator.h"

class BubbleAllocator : public Allocator
{
  public:
    BubbleAllocator(Address start, Size size);
    virtual Size size();
    virtual Size available();
    virtual Result allocate(Size *size, Address *addr, Size align = ZERO);
    virtual Result release(Address addr);
    
  private:
    u8 *m_start;
    u8 *m_current;
    Size m_size;
};

#endif /* __LIBALLOC_BUBBLEALLOCATOR_H */
