#include <KernelLog.h>
#include <StdioLog.h>
#include <fcntl.h>
#include <unistd.h>
#include "CoreServer.h"

int main(int argc, char **argv)
{
#if defined(INTEL) && defined(STDIO_LOGGING) 
    StdioLog log;
    SystemInformation info;

    if (info.coreId == 0)
    {
        close(0);
        close(1);
        close(2);

        while (open("/console/tty0", O_RDWR) == -1);
        open("/console/tty0", O_RDWR);
        open("/console/tty0", O_RDWR);
    }
#else
    KernelLog log;
#endif

    log.setMinimumLogLevel(Log::Notice);
    NOTICE("initializing on core0");

    CoreServer server;
    server.initialize();
    server.test();
    return server.runCore();
}
