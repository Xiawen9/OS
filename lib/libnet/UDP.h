#ifndef __LIBNET_UDP_H
#define __LIBNET_UDP_H

#include <Types.h>
#include <Index.h>
#include <String.h>
#include <HashTable.h>
#include "NetworkProtocol.h"
#include "IPV4.h"
#include "UDPSocket.h"

class UDPFactory;
class ARP;

/**
 * User Datagram Protocol (UDP)
 */
class UDP : public NetworkProtocol
{
  public:

    /**
     * Packet header format
     */
    typedef struct Header
    {
        u16 sourcePort;
        u16 destPort;
        u16 length;
        u16 checksum;
    }
    Header;

    /**
     * Constructor
     */
    UDP(NetworkServer *server,
        NetworkDevice *device);

    /**
     * Destructor
     */
    virtual ~UDP();

    /**
     * Set IP object
     */
    void setIP(::IPV4 *ip);

    /**
     * Perform initialization.
     */
    virtual Error initialize();

    /**
     * Creates an UDP socket
     *
     * @return UDPSocket object instance
     */
    UDPSocket * createSocket(String & path);

    /**
     * Process incoming network packet.
     *
     * @return Error code
     */
    virtual Error process(NetworkQueue::Packet *pkt, Size offset);

    /**
     * Bind to UDP port
     *
     * @param sock UDP socket
     * @param port The port to bind to
     * @return Error code
     */
    Error bind(UDPSocket *sock, u16 port);

    /**
     * Send packet
     */
    Error sendPacket(NetworkClient::SocketInfo *info, IOBuffer & buffer, Size size);

    /**
     * Calculate ICMP checksum
     *
     * @param header ICMP header
     * @return ICMP checksum value for the given header
     */
    static const u16 checksum(const IPV4::Header *ip,
                              const Header *header,
                              const Size datalen);

  private:

    static const ulong calculateSum(const u16 *ptr,
                                    Size bytes);

    UDPFactory *m_factory;

    Index<UDPSocket> m_sockets;

    /** Maps UDP ports to UDP sockets */
    HashTable<u16, UDPSocket *> m_ports;

    ::IPV4 *m_ipv4;
};

#endif /* __LIBNET_UDP_H */
