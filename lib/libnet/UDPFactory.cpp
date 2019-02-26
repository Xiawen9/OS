#include "UDP.h"
#include "UDPFactory.h"
#include "UDPSocket.h"

UDPFactory::UDPFactory(UDP *udp)
{
    m_udp = udp;
}

UDPFactory::~UDPFactory()
{
}

Error UDPFactory::read(IOBuffer & buffer, Size size, Size offset)
{
    DEBUG("");

    String path;
    UDPSocket *sock;

    if (offset > 0)
        return 0;

    sock = m_udp->createSocket(path);
    if (!sock)
        return EIO;

    buffer.write(*path, path.length() + 1);
    return path.length() + 1;
}
