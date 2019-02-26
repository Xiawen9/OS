#ifndef __LIBARCH_ARM_FIRSTTABLE_H
#define __LIBARCH_ARM_FIRSTTABLE_H

#include <System.h>
#include <Types.h>
#include <MemoryContext.h>
#include "ARMSecondTable.h"

/** Forward declaration */
class SplitAllocator;

/**
 * ARM first level page table
 */
class ARMFirstTable
{
  public:

    /**
     * Map a virtual address to a physical address.
     *
     * @param virt Virtual address.
     * @param phys Physical address.
     * @param access Memory access flags.
     * @param alloc Physical memory allocator for extra page tables.
     * @return Result code
     */
    MemoryContext::Result map(Address virt,
                              Address phys,
                              Memory::Access access,
                              SplitAllocator *alloc);

    /**
     * Map a contigous range of virtual memory to physical memory.
     *
     * This function can map at the granularity of 1 megabyte memory chunks.
     *
     * @param range Virtual to physical memory range.
     * @param alloc Physical memory allocator for extra page tables.
     * @return Result code
     */
    MemoryContext::Result mapLarge(Memory::Range range,
                                   SplitAllocator *alloc);

    /**
     * Remove virtual address mapping.
     *
     * @param virt Virtual address.
     * @return Result code
     */
    MemoryContext::Result unmap(Address virt,
                                SplitAllocator *alloc);

    /**
     * Translate virtual address to physical address.
     *
     * @param virt Virtual address to lookup on input, physical address on output.
     * @return Result code
     */
    MemoryContext::Result translate(Address virt,
                                    Address *phys,
                                    SplitAllocator *alloc);

    /**
     * Get Access flags for a virtual address.
     *
     * @param virt Virtual address to get Access flags for.
     * @param access MemoryAccess object pointer.
     * @return Result code.
     */
    MemoryContext::Result access(Address virt,
                                 Memory::Access *access,
                                 SplitAllocator *alloc);

  private:

    ARMSecondTable * getSecondTable(Address virt, SplitAllocator *alloc);

    /**
     * Convert Memory::Access to first level page table flags.
     */
    u32 flags(Memory::Access access);

    /** Array of page table entries. */
    u32 m_tables[4096];
};

#endif /* __LIBARCH_ARM_FIRSTTABLE_H */
