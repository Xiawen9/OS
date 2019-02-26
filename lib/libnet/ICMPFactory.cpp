#include "ICMPFactory.h"
#include "ICMPSocket.h"

ICMPFactory::ICMPFactory(ICMP *icmp)
{
    m_icmp = icmp;
}

ICMPFactory::~ICMPFactory()
{
}

Error ICMPFactory::read(IOBuffer & buffer, Size size, Size offset)
{
    DEBUG("");

    String path;
    ICMPSocket *sock;

    if (offset > 0)
        return 0;

    sock = m_icmp->createSocket(path);
    if (!sock)
        return EIO;

    buffer.write(*path, path.length() + 1);
    return path.length() + 1;
}
