#ifndef __LIBARCH_MEMORYMAP_H
#define __LIBARCH_MEMORYMAP_H

#include "Memory.h"

#define MEMORYMAP_MAX_REGIONS 7

/**
 * Describes virtual memory map layout
 */
class MemoryMap
{
  public:

    /**
     * Memory regions.
     *
     * Various memory regions which are available on the system.
     * Memory regions are labels which refer to predefined virtual memory ranges.
     * The virtual memory address range of each region depends on the
     * architecture implementation and can be obtained with region().
     *
     * @see region
     */
    typedef enum Region
    {
        KernelData,    /**<< Kernel program data from libexec, e.g. code, bss, (ro)data */
        KernelPrivate, /**<< Kernel dynamic memory mappings */
        UserData,      /**<< User program data from libexec, e.g. code, bss, (ro)data */
        UserHeap,      /**<< User heap */
        UserStack,     /**<< User stack */
        UserPrivate,   /**<< User private dynamic memory mappings */
        UserShare,     /**<< User shared dynamic memory mappings */
    }
    Region;

    /**
     * Constructor.
     */
    MemoryMap();

    /**
     * Copy Constructor.
     */
    MemoryMap(const MemoryMap &map);

    /**
     * Get memory range for the given region.
     *
     * @param region Memory region.
     * @return Memory::Range object
     */
    Memory::Range range(Region region);

    /**
     * Set memory range for the given region.
     */
    void setRange(Region region, Memory::Range range);

  protected:

    /** Memory ranges. */
    Memory::Range m_regions[MEMORYMAP_MAX_REGIONS];
};

#endif /* __LIBARCH_MEMORYMAP_H */
