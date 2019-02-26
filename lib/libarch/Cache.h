#ifndef __LIBARCH_CACHE_H
#define __LIBARCH_CACHE_H

#include <Types.h>
#include <Macros.h>

/**
 * Cache management interface.
 */
class Cache
{
  public:

    /**
     * Result codes
     */
    enum Result
    {
        Success,
        InvalidArgument,
        IOError
    };

    /**
     * Cache types
     */
    enum Type
    {
        Instruction,
        Data,
        Unified
    };

  public:

    /**
     * Invalidate the entire cache.
     *
     * @param type Cache type to invalidate.
     * @return Result code
     */
    virtual Result invalidate(Type type) = 0;

    /**
     * Clean and invalidate entire cache.
     *
     * This operation will clean and invalidate the
     * entire given cache.
     *
     * @param type Cache type to clean and invalidate.
     * @return Result code
     */
    virtual Result cleanInvalidate(Type type) = 0;

    /**
     * Clean and invalidate one memory page.
     *
     * @param type Cache type to clean and invalidate.
     * @param addr Virtual memory address of the page to clean and invalidate
     * @return Result code
     */
    virtual Result cleanInvalidateAddress(Type type, Address addr) = 0;

    /**
     * Clean one memory page.
     *
     * @param type Cache type to clean
     * @param addr Virtual memory address of the page to clean and invalidate
     * @return Result code
     */
    virtual Result cleanAddress(Type type, Address addr) = 0;

    /**
     * Clean one data page.
     *
     * @param addr Virtual memory address to clean
     * @return Result code
     */
    virtual Result cleanData(Address addr);

    /**
     * Clean one data page.
     *
     * @param ptr Pointer with a virtual memory address to clean
     * @return Result code
     */
    virtual Result cleanData(void *ptr);
};

#endif /* __LIBARCH_CACHE_H */
