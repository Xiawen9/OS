#include <DeviceServer.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

#include "Time.h"

int main(int argc, char **argv)
{
    DeviceServer server("/dev/time");
    server.initialize();    

    /*
     * Start serving requests
     */
    Time* t = new Time();
    server.registerDevice(t, "rtc0");
    return server.run();
}
