#include <Log.h>
#include <String.h>
#include "IPV4Address.h"

IPV4Address::IPV4Address(IPV4 *ipv4)
{
    m_ipv4 = ipv4;
}

IPV4Address::~IPV4Address()
{
}

Error IPV4Address::read(IOBuffer & buffer, Size size, Size offset)
{
    IPV4::Address addr;
    String str;

    m_ipv4->getAddress(&addr);
    str << IPV4::toString(addr);

    if (offset >= str.length())
        return 0;

    DEBUG("address = " << *str);

    buffer.write(*str, str.length());
    return str.length();
}

Error IPV4Address::write(IOBuffer & buffer, Size size, Size offset)
{
    IPV4::Address addr;
    char tmp[32];
    Error r;

    buffer.read(tmp, size < sizeof(tmp) ? size : sizeof(tmp));
    tmp[sizeof(tmp) - 1] = 0;

    DEBUG("address = " << tmp);

    // Try to convert text dotted notation to IPV4::Address
    addr = IPV4::toAddress(tmp);
    if (!addr)
        return ERANGE;

    // Set the address
    if ((r = m_ipv4->setAddress(&addr)) == ESUCCESS)
        return size;
    else
        return r;
}
