#include <System.h>
#include "Ethernet.h"
#include "IPV4.h"
#include "ARP.h"
#include "ARPSocket.h"

ARPSocket::ARPSocket(ARP *arp)
    : NetworkSocket(arp->getMaximumPacketSize())
{
    m_arp = arp;
    m_ipAddr = 0;
    MemoryBlock::set(&m_ethAddr, 0, sizeof(Ethernet::Address));
}

ARPSocket::~ARPSocket()
{
}

Error ARPSocket::read(IOBuffer & buffer, Size size, Size offset)
{
    DEBUG("");

    if (size != sizeof(Ethernet::Address))
        return ERANGE;

    if (offset >= sizeof(Ethernet::Address))
        return 0;

    Error r = m_arp->lookupAddress(&m_ipAddr, &m_ethAddr);
    if (r != ESUCCESS)
        return r;

    buffer.write(&m_ethAddr, sizeof(Ethernet::Address));
    return sizeof(Ethernet::Address);
}

Error ARPSocket::write(IOBuffer & buffer, Size size, Size offset)
{
    DEBUG("");

    // Save the request address
    buffer.read(&m_ipAddr, sizeof(IPV4::Address));

    // Send request
    // return m_arp->sendRequest(m_ipAddr);
    Error r = m_arp->lookupAddress(&m_ipAddr, &m_ethAddr);
    if (r != ESUCCESS)
        return r;
    else
        return size;
}

Error ARPSocket::process(NetworkQueue::Packet *pkt)
{
    DEBUG("");

/*
    const Ethernet::Header *ether = (Ethernet::Header *) pkt->data;
    const ARP::Header *arp = (ARP::Header *) (ether+1);

    MemoryBlock::copy(&m_ethAddr, &arp->etherSource, sizeof(Ethernet::Address));
    m_ethFound = true;
 */
    return ESUCCESS;
}

void ARPSocket::error(Error err)
{
    DEBUG("");

    // Set the ethernet reply result code
    // The read operation uses the result code
    // m_ethResult = err;
}
