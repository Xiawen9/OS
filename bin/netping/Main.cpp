#include <Log.h>
#include <KernelLog.h>
#include "NetPing.h"

int main(int argc, char **argv)
{
    /*
     * TODO: StdioLog does not work yet for libipc because inside ChannelClient()
     * there may also be a call to DEBUG() or ERROR().
     */
    KernelLog log;
    log.setMinimumLogLevel(Log::Notice);

    NetPing app(argc, argv);
    return app.run();
}
