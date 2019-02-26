#include <System.h>
#include <FileSystemMount.h>
#include <Runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char cmd[PAGESIZE];

int main(int argc, char **argv)
{
    refreshMounts(0);
    FileSystemMount *mounts = getMounts();

    // TODO: ask the kernel for the process table instead. With ARGV_ADDR copies.

    // Print header
    printf("PATH                 FILESYSTEM\r\n");

    // Print out
    for (Size i = 0; i < FILESYSTEM_MAXMOUNTS; i++)
    {
        if (mounts[i].path[0])
        {
            // Get the command
            VMCopy(mounts[i].procID, API::Read, (Address) cmd, ARGV_ADDR, PAGESIZE);
            printf("%20s %s\r\n", mounts[i].path, cmd);
        }
    }
    // Done
    return EXIT_SUCCESS;
}
