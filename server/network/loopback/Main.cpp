#include <KernelLog.h>
#include <NetworkServer.h>
#include "Loopback.h"

int main(int argc, char **argv)
{
    KernelLog log;
    log.setMinimumLogLevel(Log::Notice);

    NetworkServer server("/network/loopback");

    server.initialize();
    server.registerDevice(new Loopback(&server), "io");

    /*
     * Start serving requests
     */
    return server.run();
}
