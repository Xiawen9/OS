#ifndef __LIBNET_ICMPSOCKET_H
#define __LIBNET_ICMPSOCKET_H

#include "NetworkSocket.h"
#include "NetworkQueue.h"
#include "NetworkClient.h"

class ICMP;

/**
 * Internet Control Message Protocol (ICMP) socket.
 *
 * ICMP sockets are associated with one IP-host and
 * receive packets from that host and allow sending packets
 * to that host.
 */
class ICMPSocket : public NetworkSocket
{
  public:

    /**
     * Constructor
     */
    ICMPSocket(ICMP *icmp);

    /**
     * Destructor
     */
    virtual ~ICMPSocket();

    /**
     * Get associated IP host
     *
     * @return IPV4::Address of the connected host
     */
    const IPV4::Address getAddress() const;

    /**
     * Receive ICMP response
     *
     * @param buffer Input/Output buffer to output bytes to.
     * @param size Number of bytes to read, at maximum.
     * @param offset Offset inside the file to start reading.
     * @return Number of bytes read on success, Error on failure.
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

    /**
     * Send ICMP request
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

    /**
     * Set ICMP reply
     *
     * @param reply ICMP reply header
     */
    void setReply(ICMP::Header *reply);

    bool operator == (const ICMPSocket & sock) const
    {
        return true;
    }
    bool operator != (const ICMPSocket & sock) const
    {
        return false;
    }

  private:

    /** ICMP protocol instance */
    ICMP *m_icmp;

    /** Reply */
    ICMP::Header m_reply;
    bool m_gotReply;
};

#endif /* __LIBNET_ICMPSOCKET_H */
