#include <System.h>
#include <KernelLog.h>
#include <stdlib.h>
#include "TmpFileSystem.h"

int main(int argc, char **argv)
{
    SystemInformation info;
    const char *path = "/mount";

    // Only run on core0
    if (info.coreId != 0)
        return EXIT_SUCCESS;

    KernelLog log;
    log.setMinimumLogLevel(Log::Notice);

    if (argc > 1)
        path = argv[1];

    TmpFileSystem server(path);
    
    /*
     * Mount, then start serving requests.
     */
    server.mount();
    return server.run();
}
