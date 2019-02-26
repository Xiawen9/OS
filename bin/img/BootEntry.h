#ifndef __IMG_BOOTENTRY_H
#define __IMG_BOOTENTRY_H

#include <ExecutableFormat.h>

/** Maximum memory regions. */
#define MAX_REGIONS	16

/**
 * Executable for use inside a BootImage.
 */
typedef struct BootEntry
{
    /** BootSymbol definition */
    BootSymbol symbol;

    /** Memory regions for this symbol */
    ExecutableFormat::Region regions[MAX_REGIONS];
    
    /** Number of memory regions. */
    Size numRegions;
}
BootEntry;

#endif /* __IMG_BOOTENTRY_H */
