#ifndef __LIBPOSIX_FILEDESCRIPTOR_H
#define __LIBPOSIX_FILEDESCRIPTOR_H

#include <Types.h>
#include <Macros.h>
#include <String.h>
#include <string.h>
#include "limits.h"

#define FILE_DESCRIPTOR_MAX 1024

// TODO: move this to libfs

/**
 * Abstracts a file which is opened by a user process.
 */
class FileDescriptor
{
  public:

    FileDescriptor()
    {
        mount    = 0;
        path[0]  = ZERO;
        position = 0;
        open     = false;
    }

    FileDescriptor(const FileDescriptor & fd)
    {
        mount    = fd.mount;
        position = fd.position;
        open     = fd.open;
        strlcpy(path, fd.path, PATH_MAX);
    }

    // TODO: please modify libstd's Array/Sequence, such that I do not
    // need to implement these. I prefer to just specify a struct.

    bool operator == (const FileDescriptor & fd) const
    {
        return fd.mount == mount && strcmp(path, fd.path) == 0;
    }

    bool operator != (const FileDescriptor & fd) const
    {
        return !(fd.mount == mount && strcmp(path, fd.path) == 0);
    }

    /** Filesystem or device server on which this file was opened. */
    ProcessID mount;

    /** Unique identifier, used by a device driver (minor device ID). */
    Address identifier;

    /** Path to the file. */
    char path[PATH_MAX];

    /** Current position indicator. */
    Size position;

    /** State of the file descriptor. */
    bool open;
};

#endif /* __LIBPOSIX_FILEDESCRIPTOR_H */
