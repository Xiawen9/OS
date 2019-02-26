#ifndef __LIBARCH_INTEL_PAGETABLE_H
#define __LIBARCH_INTEL_PAGETABLE_H

#include <Types.h>
#include <Memory.h>
#include <MemoryContext.h>

/**
 * Intel page table implementation.
 */
class IntelPageTable
{
  public:

    /**
     * Map a virtual address to a physical address.
     *
     * @param virt Virtual address.
     * @param phys Physical address.
     * @param access Memory access flags.
     * @return Result code
     */
    MemoryContext::Result map(Address virt,
                              Address phys,
                              Memory::Access);

    /**
     * Remove virtual address mapping.
     *
     * @param virt Virtual address.
     * @return Result code
     */
    MemoryContext::Result unmap(Address virt);

    /**
     * Translate virtual address to physical address.
     *
     * @param virt Virtual address to lookup on input, physical address on output.
     * @return Result code
     */
    MemoryContext::Result translate(Address virt, Address *phys);

    /**
     * Get Access flags for a virtual address.
     *
     * @param virt Virtual address to get Access flags for.
     * @param access MemoryAccess object pointer.
     * @return Result code.
     */
    MemoryContext::Result access(Address virt, Memory::Access *access);

  private:

    /**
     * Convert MemoryAccess to page directory flags.
     */
    u32 flags(Memory::Access access);

    /** Array of page table entries. */
    u32 m_pages[1024];
};

#endif /* __LIBARCH_INTEL_PAGETABLE_H */
