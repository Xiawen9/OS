#ifndef __FILESYSTEM_FILE_SYSTEM_MOUNT_H
#define __FILESYSTEM_FILE_SYSTEM_MOUNT_H

#include <Types.h>
#include "limits.h"

// TODO: move this to libfs

/** Maximum number of mounted filesystems. */
#define FILESYSTEM_MAXMOUNTS 16

/**
 * Represents a mounted filesystem.
 */
typedef struct FileSystemMount
{
    /** Path of the mount. */
    char path[PATH_MAX];
    
    /** Server which is responsible for the mount. */
    ProcessID procID;
    
    /** Mount options. */
    ulong options;
}
FileSystemMount;

#endif /* __FILESYSTEM_FILE_SYSTEM_MOUNT_H */
