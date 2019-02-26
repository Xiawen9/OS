#ifndef __FILESYSTEM_TMPFILESYSTEM_H
#define __FILESYSTEM_TMPFILESYSTEM_H

#include <FileSystem.h>
#include <FileSystemMessage.h>
#include <FileSystemPath.h>
#include <Types.h>

/** 
 * @defgroup tmpfs tmpfs (Temporary Filesystem) 
 * @{ 
 */

/**
 * Temporary filesystem (procfs). Maps files into virtual memory.
 */
class TmpFileSystem : public FileSystem
{
  public:
    
    /**
     * Class constructor function.
     * @param path Path to which we are mounted.
     */
    TmpFileSystem(const char *path);

    /**
     * @brief Creates a new TmpFile.
     * @param path Full path to the file to create.
     * @param type Describes the file type to create.
     * @param deviceID Optionally specifies which device identities to use.
     * @return Pointer to a new File on success, or ZERO on failure.
     *
     * @see File
     * @see FileSystemPath
     */
    virtual File * createFile(FileType type, DeviceID deviceID);
};

/**
 * @}
 */

#endif /* __FILESYSTEM_TMPFILESYSTEM_H */
