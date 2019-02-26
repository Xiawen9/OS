#include <FileType.h>
#include <DeviceServer.h>
#include "Keyboard.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    DeviceServer server("/dev/ps2");
    server.initialize();

    /* Create a new keyboard object. */
    Keyboard *kb = new Keyboard;

    /* Register it with the DeviceServer. */
    server.registerDevice(kb, "keyboard0");
    server.registerInterrupt(kb, PS2_IRQ);

    /*
     * Start processing requests.
     */
    return server.run();
}
