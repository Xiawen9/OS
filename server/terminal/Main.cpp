#include <DeviceServer.h>
#include "Terminal.h"
#include <stdlib.h>
#include <unistd.h>
#include <Runtime.h>

int main(int argc, char **argv)
{
    DeviceServer server("/console");
    server.initialize();

    refreshMounts(0);

    /*
     * Start serving requests.
     */
    server.registerDevice(new Terminal, "tty0");
    return server.run();
}
