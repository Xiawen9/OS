#include <System.h>
#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char * states[] =
{
    "Running",
    "Ready",
    "Stopped",
    "Sleeping",
    "Waiting"
};

char cmd[PAGESIZE];

int main(int argc, char **argv)
{
    ProcessInfo info;

    // TODO: ask the kernel for the whole process table in one shot.

    // Print header
    printf("ID  PARENT  USER GROUP STATUS     CMD\r\n");

    memset(&cmd, 0, sizeof(cmd));

    // Loop processes
    for (uint i = 0; i < MAX_PROCS; i++)
    {
        // Request kernel's process information
        if (ProcessCtl(i, InfoPID, (Address) &info) != API::NotFound)
        {
            // Get the command
            VMCopy(i, API::Read, (Address) cmd, ARGV_ADDR, PAGESIZE);

            // Output a line
            printf("%3d %7d %4d %5d %10s %32s\r\n",
                    i,
                    info.parent, 0, 0,
                    states[info.state], cmd);
        }
    }
    return EXIT_SUCCESS;
}
