#ifndef __LIBALLOC_SPLITALLOCATOR_H
#define __LIBALLOC_SPLITALLOCATOR_H

#include <Types.h>
#include "Allocator.h"
#include "BitAllocator.h"
/**
 * Allocator which separates kernel mapped low-memory and higher memory.
 */
class SplitAllocator : public Allocator
{
  public:
    SplitAllocator(Memory::Range low, Memory::Range high);
    virtual ~SplitAllocator();
    virtual Size size();
    virtual Size available();
    virtual Result allocate(Size *size, Address *addr, Size align = ZERO);
    Result allocate(Address addr);

    /**
     * Allocate from lower memory.
     *
     * @param size Amount of memory in bytes to allocate.
     * @param addr Output parameter which contains the address
     *             allocated on success.
     * @param align Alignment of the required memory or use ZERO for default.
     * @return Result code
     */
    virtual Result allocateLow(Size size, Address *addr, Size align = ZERO);
    virtual Result allocateHigh(Size size, Address *addr, Size align = ZERO);
    virtual Result release(Address addr);
    void * toVirtual(Address phys);

  private:
    BitAllocator *m_alloc;
    Memory::Range m_low;
    Memory::Range m_high;
};

#endif /* __LIBALLOC_SPLITALLOCATOR_H */
