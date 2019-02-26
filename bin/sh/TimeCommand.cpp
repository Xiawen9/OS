#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include "TimeCommand.h"

TimeCommand::TimeCommand() : ShellCommand("time", 1)
{
    m_help = "Measure the execution time of a program";
}

int TimeCommand::execute(Size nparams, char **params)
{
    struct timeval t1, t2;
    struct timezone zone;
    int pid;
    int status;
    char tmp[128];

    // Get timestamp before
    gettimeofday(&t1, &zone);

    // If not, try to execute it as a file directly. */
    if ((pid = forkexec(params[0], (const char **) params)) != -1)
    {
        waitpid(pid, &status, 0);
    }
    // Try to find it on the livecd filesystem. (temporary hardcoded PATH)
    else if (snprintf(tmp, sizeof(tmp), "/bin/%s", params[0]) &&
            (pid = forkexec(tmp, (const char **) params)) != -1)
    {
        waitpid(pid, &status, 0);
    }
    else
    {
        printf("forkexec '%s' failed: %s\r\n", params[0],
                strerror(errno));
        return EXIT_FAILURE;
    }
    // Get timestamp after
    gettimeofday(&t2, &zone);

    // Print time measured
    printf("\r\nTime: ");
    printtimediff(&t1, &t2);
    printf("\r\n");
    return 0;
}
