#include <KernelLog.h>
#include <DeviceServer.h>
#include <USBHub.h>

int main(int argc, char **argv)
{
    KernelLog log;
    log.setMinimumLogLevel(Log::Notice);

    DeviceServer server("/usbhub");
    server.initialize();
    server.registerDevice(new USBHub(1), "roothub");

    /*
     * Start serving requests
     */
    return server.run();
}
