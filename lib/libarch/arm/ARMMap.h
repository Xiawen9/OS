#ifndef __LIBARCH_ARMMAP_H
#define __LIBARCH_ARMMAP_H

#include <MemoryMap.h>

class ARMMap : public MemoryMap
{
  public:

    /**
     * Constructor.
     */
    ARMMap();
};

namespace Arch
{
    typedef ARMMap MemoryMap;
};

#endif /* __LIBARCH_ARMMAP_H */
