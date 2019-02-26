#ifndef __LIBNET_ARPSOCKET_H
#define __LIBNET_ARPSOCKET_H

#include "IPV4.h"
#include "NetworkSocket.h"
#include "NetworkQueue.h"

class ARP;

/**
 * Address Resolution Protocol (ARP) socket.
 *
 * ARP sockets receive a copy of ARP reply packets.
 */
class ARPSocket : public NetworkSocket
{
  public:

    /**
     * Constructor
     */
    ARPSocket(ARP *arp);

    /**
     * Destructor
     */
    virtual ~ARPSocket();

    /**
     * Receive ARP response
     *
     * @param buffer Input/Output buffer to output bytes to.
     * @param size Number of bytes to read, at maximum.
     * @param offset Offset inside the file to start reading.
     * @return Number of bytes read on success, Error on failure.
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

    /**
     * Send ARP request
     *
     * @param buffer Input/Output buffer to input bytes from.
     * @param size Number of bytes to write, at maximum.
     * @param offset Offset inside the file to start writing.
     * @return Number of bytes written on success, Error on failure.
     */
    virtual Error write(IOBuffer & buffer, Size size, Size offset);

    /**
     * Process incoming network packet.
     *
     * @return Error code
     */
    virtual Error process(NetworkQueue::Packet *pkt);

    /**
     * Set error status
     *
     * @param err Error code
     */
    virtual void error(Error err);

  private:

    /** ARP protocol instance */
    ARP *m_arp;

    /** IPV4 address for request. */
    IPV4::Address m_ipAddr;

    /** Ethernet address for reply. */
    Ethernet::Address m_ethAddr;

    /** Set if ethernet address was received */
    bool m_ethFound;
};

#endif /* __LIBNET_ARPSOCKET_H */
