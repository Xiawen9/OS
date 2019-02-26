#include "Cache.h"

Cache::Result Cache::cleanData(Address addr)
{
    return cleanAddress(Data, addr);
}

Cache::Result Cache::cleanData(void *ptr)
{
    return cleanAddress(Data, (Address) ptr);
}
