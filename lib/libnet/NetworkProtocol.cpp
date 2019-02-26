#include "NetworkDevice.h"
#include "NetworkProtocol.h"

NetworkProtocol::NetworkProtocol(NetworkServer *server,
                                 NetworkDevice *device)
{
    m_server = server;
    m_device = device;
}

NetworkProtocol::~NetworkProtocol()
{
}

const Size NetworkProtocol::getMaximumPacketSize() const
{
    return m_device->getMaximumPacketSize();
}
