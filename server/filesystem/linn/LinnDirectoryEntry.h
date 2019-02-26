#ifndef __FILESYSTEM_LINN_DIRECTORY_ENTRY_H
#define __FILESYSTEM_LINN_DIRECTORY_ENTRY_H

#include <Types.h>

/**
 * @defgroup linn LinnFS (Linnenbank Filesystem) 
 * @{
 */

/**
 * Calculates the number of LinnDirectoryEntry's fitting in one block.
 * @return Number of entries.
 */
#define LINN_DIRENT_PER_BLOCK(sb) \
    ((sb)->blockSize / sizeof(LinnDirectoryEntry))

/** Length of the name field in an directory entry. */
#define LINN_DIRENT_NAME_LEN 59

/**
 * Struct of an directory entry in LinnFS.
 */
typedef struct LinnDirectoryEntry
{
    /** Inode number. */
    le32 inode;

    /** Type of file, as an FileType. */
    u8 type;

    /** File name. Null terminated. */
    char name[LINN_DIRENT_NAME_LEN];
}
LinnDirectoryEntry;

/**
 * @}
 */

#endif /* __FILESYSTEM_LINN_DIRECTORY_ENTRY_H */
