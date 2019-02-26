#ifndef __LIBNET_ICMP_H
#define __LIBNET_ICMP_H

#include <Types.h>
#include <Index.h>
#include <String.h>
#include "NetworkProtocol.h"
#include "IPV4.h"

class ICMPFactory;
class ICMPSocket;
class ARP;

/**
 * Internet Control Message Protocol (ICMP)
 */
class ICMP : public NetworkProtocol
{
  public:

    /**
     * Packet types
     */
    enum Type
    {
        EchoReply = 0,
        DestinationUnreachable = 3,
        Redirect = 5,
        EchoRequest = 8
    };

    /**
     * Packet header format
     */
    typedef struct Header
    {
        u8 type;
        u8 code;
        u16 checksum;
        u16 id;
        u16 sequence;
    }
    Header;

    /**
     * Constructor
     */
    ICMP(NetworkServer *server,
         NetworkDevice *device);

    /**
     * Destructor
     */
    virtual ~ICMP();

    /**
     * Set IP object
     */
    void setIP(::IPV4 *ip);

    /**
     * Perform initialization.
     */
    virtual Error initialize();

    /**
     * Creates an ICMP socket
     *
     * @return ICMPSocket object instance
     */
    ICMPSocket * createSocket(String & path);

    /**
     * Process incoming network packet.
     *
     * @return Error code
     */
    virtual Error process(NetworkQueue::Packet *pkt, Size offset);

    /**
     * Send packet
     */
    Error sendPacket(IPV4::Address ip, Header *header);

    /**
     * Calculate ICMP checksum
     *
     * @param header ICMP header
     * @return ICMP checksum value for the given header
     */
    static const u16 checksum(Header *header);

  private:

    ICMPFactory *m_factory;

    Index<ICMPSocket> m_sockets;

    ::IPV4 *m_ipv4;
};

#endif /* __LIBNET_ICMP_H */
