#ifndef __LIBALLOC_POOLALLOCATOR_H
#define __LIBALLOC_POOLALLOCATOR_H

#include <Types.h>
#include <Macros.h>
#include "Allocator.h"

#define POOL_MIN_POWER 2
#define POOL_MAX_POWER 32
#define POOL_MIN_COUNT(size) \
    (64 / (((size) / 1024 ) + 1)) > 0 ? \
    (64 / (((size) / 1024 ) + 1)) : 1
#define BITMAP_NUM_BYTES(count) \
    ((count / 8) + 1)

typedef struct MemoryPool
{
    /**
     * Marks the appropriate bits in the free and used block bitmap.
     * @return Pointer to the next available block, if any.
     */
    Address allocate()
    {
        Address *ptr;
        Size num = count / sizeof(Address);
    
        /* At least one. */
        if (!num) num++;

        /* Scan bitmap as fast as possible. */
        for (Size i = 0; i < num; i++)
        {
            /* Point to the correct offset. */
            ptr = (Address *) (&blocks) + i;
    
            /* Any blocks free? */
            if (*ptr != (Address) ~ZERO)
            {
                /* Find the first free bit. */
                for (Size bit = 0; bit < sizeof(Address) * 8; bit++)
                {
                    if (!(*ptr & 1 << bit))
                    {
                        *ptr |= (1 << bit);
                        free--;
                        return addr + (((i * sizeof(Address) * 8) + bit) * size);
                    }
                }
            }
        }
        /* Out of memory. */
        return ZERO;
    }

    /**
     * Unmarks the appropriate bit for the given address.
     * @param a Address to unmark.
     */
    void release(Address a)
    {
        Size index = (a - addr) / size / 8;
        Size bit   = (a - addr) / size % 8;
    
        free++;
        blocks[index] &= ~(1 << bit);
    }

    /** Points to the next pool of this size (if any). */
    MemoryPool *next;
    
    /** Memory address allocated to this pool. */
    Address addr;

    /** Size of each object in the pool. */
    Size size;

    /** Number of blocks in the pool. */
    Size count;
    
    /** Free blocks left. */
    Size free;
    
    /** Bitmap which represents free and used blocks. */
    u8 blocks[];
}
MemoryPool;
class PoolAllocator : public Allocator
{
  public:
    PoolAllocator();
    virtual Size size();
    virtual Size available();
    virtual Result allocate(Size *size, Address *addr, Size align = ZERO);
    virtual Result release(Address addr);

  private:
    MemoryPool * newPool(Size index, Size cnt);
    MemoryPool *m_pools[POOL_MAX_POWER];
};

#endif /* __LIBALLOC_POOLALLOCATOR_H */
