#include <FileType.h>
#include <DeviceServer.h>
#include "VGA.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    DeviceServer server("/dev/video");
    server.initialize();

    /*
     * Start serving requests.
     */    
    server.registerDevice(new VGA, "vga0");
    return server.run();
}
