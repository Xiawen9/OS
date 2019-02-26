#include <File.h>
#include <PseudoFile.h>
#include <Directory.h>
#include "TmpFileSystem.h"

TmpFileSystem::TmpFileSystem(const char *path)
    : FileSystem(path)
{
    setRoot(new Directory);
}

File * TmpFileSystem::createFile(FileType type, DeviceID deviceID)
{
    // Create the appropriate file type
    switch (type)
    {
        case RegularFile:
            return new PseudoFile;

        case DirectoryFile:
            return new Directory;

        default:
            return ZERO;
    }
}
