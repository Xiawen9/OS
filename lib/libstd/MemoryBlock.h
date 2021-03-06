#ifndef __MEMORYBLOCK_H
#define __MEMORYBLOCK_H

#include "Types.h"

class MemoryBlock
{
  public:
    static void * set(void *dest, int ch, unsigned count);
    static Size copy(void *dest, const void *src, Size count);
    static Size copy(char *dest, char *src, Size count);

    /**
     * Compare memory.
     */
    static bool compare(void *dest, void *src, Size count);

    /**
     * Compare memory.
     *
     * @param p1 Memory pointer one.
     * @param p2 Memory pointer two.
     * @param count Number of bytes to compare or zero to continue until a ZERO byte.
     * @return True if equal, false otherwise.
     */
    static bool compare(const char *p1, const char *p2, Size count = 0);
};

#endif /* __MEMORYBLOCK_H */
