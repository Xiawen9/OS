#include <System.h>
#include <KernelLog.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
    SystemInformation info;
    const char *av[] = { "/bin/sh", "/etc/init.sh", ZERO };

    // Only run on core0
    if (info.coreId != 0)
        return EXIT_SUCCESS;

    /* Open kernel logging facilities. */
    Log *log = new KernelLog();
    log->setMinimumLogLevel(Log::Notice);

    /*
     * TODO: give up all privileges.
     */
    NOTICE("Starting init script: " << av[1]);

    // Execute the run commands file
    if (forkexec("/bin/sh", av) == -1)
    {
        ERROR("forkexec() failed for /bin/sh: " <<
              strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
