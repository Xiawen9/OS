#include <KernelLog.h>
#include <NetworkServer.h>
#include "SMSC95xx.h"

int main(int argc, char **argv)
{
    KernelLog log;
    log.setMinimumLogLevel(Log::Notice);

    NetworkServer server("/network/smsc95xx"); // TODO: add serial code? something unique to this device.

    server.initialize();
    server.registerDevice(new SMSC95xx(2, "/usb", &server), "io");

    /*
     * Start serving requests
     */
    return server.run();
}
