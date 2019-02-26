#ifndef __LIBARCH_INTELMAP_H
#define __LIBARCH_INTELMAP_H

#include <MemoryMap.h>

class IntelMap : public MemoryMap
{
  public:

    /**
     * Constructor.
     */
    IntelMap();
};

namespace Arch
{
    typedef IntelMap MemoryMap;
};

#endif /* __LIBARCH_MEMORYMAP_H */
