#include <KernelLog.h>
#include "SynopsisController.h"

int main(int argc, char **argv)
{
    KernelLog log;
    log.setMinimumLogLevel(Log::Notice);

    SynopsisController server("/usb");
    server.initialize();

    /*
     * Start serving requests
     */
    return server.run();
}
