#include <System.h>
#include "Ethernet.h"
#include "IPV4.h"
#include "ICMP.h"
#include "ICMPSocket.h"
#include "NetworkClient.h"

ICMPSocket::ICMPSocket(ICMP *icmp)
    : NetworkSocket(icmp->getMaximumPacketSize())
{
    m_icmp = icmp;
    m_gotReply = false;
    MemoryBlock::set(&m_info, 0, sizeof(m_info));
}

ICMPSocket::~ICMPSocket()
{
}

const IPV4::Address ICMPSocket::getAddress() const
{
    return m_info.address;
}

Error ICMPSocket::read(IOBuffer & buffer, Size size, Size offset)
{
    DEBUG("");

    //if (offset >= sizeof(ICMP::Header))
    //    return 0;

    // TODO: use a timeout on the ICMP socket

    if (!m_gotReply)
        return EAGAIN;

    m_gotReply = false;
    buffer.write(&m_reply, sizeof(m_reply));
    return sizeof(m_reply);
}

Error ICMPSocket::write(IOBuffer & buffer, Size size, Size offset)
{
    DEBUG("");

    // Receive socket information first?
    if (!m_info.address)
    {
        buffer.read(&m_info, sizeof(m_info));
        return size;
    }
    else
    {
        ICMP::Header header;
        buffer.read(&header, sizeof(header));

        Error r = m_icmp->sendPacket(m_info.address, &header);
        if (r != ESUCCESS)
            return r;
    }
    return size;
}

Error ICMPSocket::process(NetworkQueue::Packet *pkt)
{
    DEBUG("");
    return ESUCCESS;
}

void ICMPSocket::error(Error err)
{
    DEBUG("");

    // Set the ethernet reply result code
    // The read operation uses the result code
    // m_ethResult = err;
}

void ICMPSocket::setReply(ICMP::Header *header)
{
    DEBUG("");

    if (!m_gotReply)
    {
        MemoryBlock::copy(&m_reply, header, sizeof(ICMP::Header));
        m_gotReply = true;
    }
}
