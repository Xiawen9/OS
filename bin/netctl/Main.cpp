#include <Log.h>
#include <KernelLog.h>
#include "NetCtl.h"

int main(int argc, char **argv)
{
    KernelLog log;
    log.setMinimumLogLevel(Log::Notice);

    NetCtl app(argc, argv);
    return app.run();
}
