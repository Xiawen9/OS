#include <MemoryBlock.h>
#include "ARMTags.h"

ARMTags::ARMTags(Address base)
{
    m_base = base;
}

Memory::Range ARMTags::getInitRd2()
{
    Memory::Range range;
    struct ATag *tag = (struct ATag *) m_base;
    
    MemoryBlock::set(&range, 0, sizeof(range));

    while (tag)
    {
        if (tag->hdr.tag == None)
            break;

        if (tag->hdr.tag == InitRd2)
        {
            range.phys = tag->u.initrd2.start;
            range.size = tag->u.initrd2.size;
            break;
        }
        tag = ((struct ATag *)((u32 *)(tag) + (tag)->hdr.size));
    }

    return range;
}
