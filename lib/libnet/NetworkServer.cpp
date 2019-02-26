#include "NetworkServer.h"

NetworkServer::NetworkServer(const char *path)
    : DeviceServer(path)
{
}

NetworkServer::~NetworkServer()
{
}

Error NetworkServer::initialize()
{
    DEBUG("");
    return DeviceServer::initialize();
}
