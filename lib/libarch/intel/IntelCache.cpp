#include "IntelCache.h"

IntelCache::Result IntelCache::invalidate(IntelCache::Type type)
{
    return Success;
}

IntelCache::Result IntelCache::cleanInvalidate(IntelCache::Type type)
{
    return Success;
}

IntelCache::Result IntelCache::cleanInvalidateAddress(Type type, Address addr)
{
    return Success;
}

IntelCache::Result IntelCache::cleanAddress(IntelCache::Type type, Address addr)
{
    return Success;
}
