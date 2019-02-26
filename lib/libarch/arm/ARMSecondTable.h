#ifndef __LIBARCH_ARM_SECONDTABLE_H
#define __LIBARCH_ARM_SECONDTABLE_H

#include <Types.h>
#include <Memory.h>
#include <MemoryContext.h>

/**
 * ARM second level page table implementation.
 */
class ARMSecondTable
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

    /** Array of second level page table entries */
    u32 m_pages[256];
};

#endif /* __LIBARCH_ARM_SECONDTABLE_H */
