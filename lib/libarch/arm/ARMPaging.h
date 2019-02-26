#ifndef __LIBARCH_ARM_PAGING_H
#define __LIBARCH_ARM_PAGING_H

#include <Types.h>
#include "MemoryContext.h"
#include "MemoryMap.h"

/** Forward declaration */
class SplitAllocator;
class ARMFirstTable;

/**
 * ARM virtual memory implementation.
 */
class ARMPaging : public MemoryContext
{
  public:

    /**
     * Constructor.
     *
     * @param map Virtual memory map.
     * @param alloc Allocator pointer of the physical memory page allocations.
     */
    ARMPaging(MemoryMap *map, SplitAllocator *alloc);

    /**
     * Destructor.
     */
    virtual ~ARMPaging();

    /**
     * Activate the MemoryContext.
     *
     * This function applies this MemoryContext to the hardware MMU.
     * @return Result code.
     */
    virtual Result activate();

    /**
     * Map a physical page to a virtual address.
     *
     * @param virt Virtual address.
     * @param phys Physical address.    
     * @param access Memory access flags.
     * @return Result code
     */     
    virtual Result map(Address virt, Address phys, Memory::Access access);

    /**
     * Unmap a virtual address.
     *
     * This function removes a virtual to physical memory
     * mapping without deallocating any physical memory.
     *
     * @param virt Virtual address to unmap.
     * @return Result code
     */
    virtual Result unmap(Address virt);

    /**
     * Translate virtual address to physical address.
     *
     * @param virt Virtual address to lookup on input, physical address on output.
     * @return Result code
     */
    virtual Result lookup(Address virt, Address *phys);

    /**
     * Get Access flags for a virtual address.
     *
     * @param virt Virtual address to get Access flags for.
     * @param access MemoryAccess object pointer.
     * @return Result code.
     */
    virtual Result access(Address addr, Memory::Access *access);

  private:

    /**
     * Enable the MMU
     *
     * @return Result code
     */
    Result enableMMU();

    /** Pointer to the first level page table. */
    ARMFirstTable *m_firstTable;

    /** Physical address of the first level page table. */
    Address m_firstTableAddr;

    /** Caching implementation */
    Arch::Cache m_cache;
};

namespace Arch
{
    typedef ARMPaging Memory;
};

#endif /* __LIBARCH_ARM_PAGING_H */
