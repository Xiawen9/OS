#ifndef __LIBALLOC_BITALLOCATOR_H
#define __LIBALLOC_BITALLOCATOR_H

#include <BitArray.h>
#include <Types.h>
#include <Memory.h>
#include "Allocator.h"

class BitAllocator : public Allocator
{
  public:
    BitAllocator(Memory::Range range, Size chunkSize);
    Size chunkSize();
    virtual Size size();
    virtual Size available();
    Address base();
    BitArray * getBitArray();
    virtual Result allocate(Size *size, Address *addr, Size align = ZERO);
    Result allocate(Size *size, Address *addr, Size align = ZERO, Address allocStart = 0);
    Result allocate(Address addr);
    bool isAllocated(Address page);
    virtual Result release(Address chunk);
  private:
    BitArray m_array;
    Address m_base;
    Size m_chunkSize;
};

#endif /* __MEMORY_H */
