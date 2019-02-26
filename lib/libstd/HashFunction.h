#ifndef __LIBSTD_HASH_FUNCTION_H
#define __LIBSTD_HASH_FUNCTION_H

#include "Types.h"
#include "String.h"

/** Prime number used by FNV hashing. */
#define FNV_PRIME 16777619

/** Initial value of the FNV internal state. */
#define FNV_INIT  0x811c9dc5

/**
 * Compute a hash using the FNV algorithm.
 *
 * @param key Key to hash.
 * @param mod Modulo value.
 * @return Computed hash.
 */
Size hash(const String & key, Size mod);

Size hash(int key, Size mod);

#endif /* __LIBSTD_HASH_FUNCTION_H */
