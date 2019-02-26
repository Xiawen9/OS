#ifndef __LIBPOSIX_RUNTIME_H
#define __LIBPOSIX_RUNTIME_H

#include <Macros.h>
#include <Types.h>
#include <Vector.h>
#include <String.h>
#include <ChannelClient.h>
#include "FileSystemMount.h"
#include "FileDescriptor.h"

/**
 * @defgroup libposix libposix (POSIX.1-2008) 
 * @{ 
 */

/**
 * C(++) program entry point.
 * @param argc Argument count.
 * @param argv Argument values.
 * @return Exit status.
 */
int main(int argc, char **argv);

/**
 * Retrieve the ProcessID of the FileSystemMount for the given path.
 * @param path Path to lookup.
 * @return ProcessID of the FileSystemMount on success and ZERO otherwise.
 */
ProcessID findMount(const char *path);

/**
 * Lookup the ProcessID of a FileSystemMount by a filedescriptor number.
 * @param fildes FileDescriptor number.
 * @return ProcessID of the FileSystemMount on success and ZERO otherwise.
 */
ProcessID findMount(int fildes);

void refreshMounts(const char *path);

/**
 * Get FileDescriptors table.
 */
Vector<FileDescriptor> * getFiles();

/**
 * Get mounts table.
 */
FileSystemMount * getMounts();

/**
 * Get current directory String.
 */
String * getCurrentDirectory();

/**
 * @}
 */

#endif /* __LIBPOSIX_RUNTIME_H */
