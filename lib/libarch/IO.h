#ifndef __LIBARCH_IO_H
#define __LIBARCH_IO_H

#include <Types.h>
#include "Memory.h"

/**
 * Generic I/O functions.
 */
class IO
{
  public:

    enum Result
    {
        Success,
        MapFailure,
        OutOfMemory
    };

    /**
     * Constructor.
     */
    IO();

    /**
     * Get I/O base offset.
     *
     * @return Base offset to add to each I/O address.
     */
    uint getBase() const;

    /**
     * Set I/O base offset.
     *
     * @param base Offset to add to each I/O address.
     */
    void setBase(uint base);

    /**
     * Map I/O address space.
     *
     * @param phys Physical address for start of the range.
     * @param size Size of the I/O address space.
     * @param access Memory access flags
     * @return Result code.
     */
    Result map(Address phys,
               Size size = 4096,
               Memory::Access access = Memory::Readable | Memory::Writable | Memory::User);

    /**
     * Unmap I/O address space.
     *
     * @return Result code.
     */
    Result unmap();

  protected:

    /** I/O base offset is added to each I/O address. */
    uint m_base;

    /** Memory range for performing I/O mappings. */
    Memory::Range m_range;
};

#endif /* __LIBARCH_IO_H */
