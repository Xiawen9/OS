#ifndef __LIBARCH_ARM_ARMCACHEV7_H
#define __LIBARCH_ARM_ARMCACHEV7_H

#include <Types.h>
#include <Macros.h>
#include <Cache.h>
#include "ARMControl.h"

/**
 * ARMv7 cache management implementation.
 *
 * @see ARM Architecture Reference Manual, page xxx
 */
class ARMCacheV7 : public Cache
{
  private:

    enum CacheLevelType
    {
        CacheLevelInstruction = 1,
        CacheLevelData        = 2,
        CacheLevelInstructionData = 3,
        CacheLevelUnified = 4
    };

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

  private:

    /**
     * Flush the entire data cache
     *
     * @param clean True to clean cache before invalidation.
     * @return Result code
     */
    Result dataFlush(bool clean);

    /**
     * Get cache level id.
     */
    u32 getCacheLevelId();

    /**
     * Get cache size.
     */
    u32 readCacheSize(u32 level, u32 type);

    /**
     * Clean and Invalidate by cache level
     *
     * @param clean True to clean cache before invalidation.
     * @return Result code
     */
    Result flushLevel(u32 level, bool clean);

    /** ARM system control processor object */
    ARMControl m_control;
};

namespace Arch
{
    typedef ARMCacheV7 Cache;
};

#endif /* __LIBARCH_ARM_ARMCACHEV7_H */
