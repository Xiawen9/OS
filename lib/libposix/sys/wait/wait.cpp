#include <System.h>
#include "sys/wait.h"
#include "sys/types.h"
#include <errno.h>

pid_t waitpid(pid_t pid, int *stat_loc, int options)
{
#warning change to API::Result later in kernel. Also in the ProcessCtl.h header etc.
    Error result = ProcessCtl(pid, WaitPID);

    if (stat_loc)
    {
        *stat_loc = result;
    }
    return result;
}
