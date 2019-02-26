#include <MemoryBlock.h>
#include "IntelMap.h"

IntelMap::IntelMap()
{
    MemoryBlock::set(m_regions, 0, sizeof(m_regions));

    m_regions[KernelData].virt      = 0;
    m_regions[KernelData].size      = GigaByte(1) - MegaByte(128);

    m_regions[KernelPrivate].virt   = GigaByte(1) - MegaByte(128);
    m_regions[KernelPrivate].size   = MegaByte(128);

    m_regions[UserData].virt      = 0x80000000;
    m_regions[UserData].size      = MegaByte(256);

    m_regions[UserHeap].virt      = 0xb0000000;
    m_regions[UserHeap].size      = MegaByte(256);

    m_regions[UserStack].virt     = 0xc0000000;
    m_regions[UserStack].size     = KiloByte(4);

    m_regions[UserPrivate].virt   = 0xa0000000;
    m_regions[UserPrivate].size   = MegaByte(256);

    m_regions[UserShare].virt     = 0xd0000000;
    m_regions[UserShare].size     = MegaByte(256);
}
