#include <Log.h>
#include "EthernetAddress.h"

EthernetAddress::EthernetAddress(Ethernet *eth)
{
    m_eth = eth;
}

EthernetAddress::~EthernetAddress()
{
}

Error EthernetAddress::read(IOBuffer & buffer, Size size, Size offset)
{
    Ethernet::Address addr;

    m_eth->getAddress(&addr);
    String s = Ethernet::toString(addr);

    if (offset >= s.length())
        return 0;

    buffer.write(*s, s.length());
    return s.length();
}

Error EthernetAddress::write(IOBuffer & buffer, Size size, Size offset)
{
    return ENOTSUP;
}
