#include <KernelLog.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    KernelLog log;
    log.setMinimumLogLevel(Log::Debug);

#if 0
    ChannelServer server;
    if (server.initialize() != ChannelServer::Success)
    {
        ERROR("failed to initialize");
        return EXIT_FAILURE;
    }
    return server.run();
#endif
    return 0;
}
