#ifndef __LIBARCH_INTEL_INTELCACHE_H
#define __LIBARCH_INTEL_INTELCACHE_H

#include <Types.h>
#include <Macros.h>
#include <Cache.h>

/**
 * Intel cache management implementation.
 */
class IntelCache : public Cache
{
  public:

    /**
     * Invalidate the entire cache.
     *
     * @param type Cache type to invalidate.
     * @return Result code
     */
    virtual Result invalidate(Type type);

    /**
     * Clean and invalidate entire cache.
     *
     * This operation will clean and invalidate the
     * entire given cache.
     *
     * @param type Cache type to clean and invalidate.
     * @return Result code
     */
    virtual Result cleanInvalidate(Type type);

    /**
     * Clean and invalidate one memory page.
     *
     * @param type Cache type to clean and invalidate.
     * @param addr Virtual memory address of the page to clean and invalidate
     * @return Result code
     */
    virtual Result cleanInvalidateAddress(Type type, Address addr);

    /**
     * Clean one memory page.
     *
     * @param type Cache type to clean
     * @param addr Virtual memory address of the page to clean and invalidate
     * @return Result code
     */
    virtual Result cleanAddress(Type type, Address addr);
};

namespace Arch
{
    typedef IntelCache Cache;
};

#endif /* __LIBARCH_INTEL_INTELCACHE_H */
