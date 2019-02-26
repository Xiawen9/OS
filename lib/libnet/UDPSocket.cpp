#include <stdlib.h>
#include "Ethernet.h"
#include "UDP.h"
#include "UDPSocket.h"

UDPSocket::UDPSocket(UDP *udp)
    : NetworkSocket(udp->getMaximumPacketSize()),
      m_queue(udp->getMaximumPacketSize())
{
    m_udp  = udp;
    m_port = 0;
}

UDPSocket::~UDPSocket()
{
}

const u16 UDPSocket::getPort() const
{
    return m_port;
}

Error UDPSocket::read(IOBuffer & buffer, Size size, Size offset)
{
    DEBUG("");

    NetworkQueue::Packet *pkt = m_queue.pop();
    if (!pkt)
        return EAGAIN;

    // TODO: assumes ethernet here
    IPV4::Header *ipHdr = (IPV4::Header *)(pkt->data + sizeof(Ethernet::Header));
    UDP::Header *udpHdr = (UDP::Header *)(pkt->data + sizeof(Ethernet::Header) + sizeof(IPV4::Header));
    NetworkClient::SocketInfo info;
    Size payloadSize = pkt->size - sizeof(Ethernet::Header)
                                 - sizeof(IPV4::Header)
                                 - sizeof(UDP::Header);

    // Fill socket info
    info.address = ipHdr->source;
    info.port    = udpHdr->sourcePort;
    buffer.write(&info, sizeof(info));

    // Fill payload
    Size sz = size > payloadSize ? payloadSize : size;
    buffer.write(udpHdr+1, sz, sizeof(info));
    m_queue.release(pkt);
    return sz + sizeof(info);
}

Error UDPSocket::write(IOBuffer & buffer, Size size, Size offset)
{
    DEBUG("");

    // Receive socket information first?
    if (!m_info.port)
    {
        buffer.read(&m_info, sizeof(m_info));

        // TODO: retry if the random port is already in use...
        // TODO: move this to the NetworkSocket
        // TODO: remove libposix dependency. Use Random from libstd later.
        if (m_info.port == 0)
            m_info.port = random() % 65535;

        DEBUG("addr =" << m_info.address << " port = " << m_info.port);

        Error r = m_udp->bind(this, m_info.port);
        if (r != ESUCCESS)
            return r;
        else
            return size;
    }
    else
        return m_udp->sendPacket(&m_info, buffer, size);
}

Error UDPSocket::process(NetworkQueue::Packet *pkt)
{
    DEBUG("");

    // TODO: for performance its better to "trade" packets instead of copying
    NetworkQueue::Packet *buf = m_queue.get();
    if (!buf)
    {
        ERROR("udp socket queue full");
        return EIO;
    }
    buf->size = pkt->size;
    MemoryBlock::copy(buf->data, pkt->data, pkt->size);
    m_queue.push(buf);
    return ESUCCESS;
}

void UDPSocket::error(Error err)
{
    DEBUG("");
}
