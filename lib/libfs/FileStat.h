#ifndef __FILESYSTEM_FILESTAT_H
#define __FILESYSTEM_FILESTAT_H

#include <Types.h>
#include "FileType.h"

/**
 * Contains file information.
 */
typedef struct FileStat
{
    /** File type. */
    FileType type;
    
    /** File access permission bits. */
    FileModes access;
    
    /** Size of the file in bytes. */
    Size size;
    
    /** User identity. */
    UserID userID;
    
    /** Group identity. */
    GroupID groupID;
    
    /** Device identity. */
    DeviceID deviceID;
}
FileStat;

#endif /* __FILESYSTEM_FILESTAT_H */
