#include <Log.h>
#include <KernelLog.h>
#include "NetCat.h"

int main(int argc, char **argv)
{
    KernelLog log;
    log.setMinimumLogLevel(Log::Notice);

    NetCat app(argc, argv);
    return app.run();
}
