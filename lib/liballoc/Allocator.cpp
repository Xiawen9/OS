#include <System.h>
#include <Macros.h>
#include "Allocator.h"

Allocator * Allocator::m_default = ZERO;

Allocator::Allocator()
{
    m_parent = ZERO;
    m_alignment = MEMALIGN;
    m_base = 0;
}

Allocator::~Allocator()
{
}

void Allocator::setParent(Allocator *parent)
{
    m_parent = parent;
}

Allocator * Allocator::getDefault()
{
    return m_default;
}

void Allocator::setDefault(Allocator *alloc)
{
    m_default = alloc;
}

Allocator::Result Allocator::setAlignment(Size size)
{
    if (size % MEMALIGN)
        return InvalidAlignment;

    m_alignment = size;
    return Success;
}

Allocator::Result Allocator::setBase(Address addr)
{
    if (addr % PAGESIZE)
        return InvalidAddress;

    m_base = addr;
    return Success;
}

Address Allocator::aligned(Address addr, Size boundary)
{
    Address corrected = addr;

    if (addr % boundary)
        corrected += boundary - (addr % boundary);
    
    return corrected;
}
