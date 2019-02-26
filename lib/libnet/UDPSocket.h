#ifndef __LIBNET_UDPSOCKET_H
#define __LIBNET_UDPSOCKET_H

#include "NetworkSocket.h"
#include "NetworkQueue.h"
#include "NetworkClient.h"

class UDP;

/**
 * User Datagram Protocol (UDP) socket.
 *
 * UDP sockets accept payloads to send when writing
 * and read payloads when receiving payloads.
 */
class UDPSocket : public NetworkSocket
{
  public:

    /**
     * Constructor
     */
    UDPSocket(UDP *udp);

    /**
     * Destructor
     */
    virtual ~UDPSocket();

    /**
     * Get associated local port.
     *
     * @return Local port
     */
    const u16 getPort() const;

    /**
     * Receive UDP data
     *
     * @param buffer Input/Output buffer to output bytes to.
     * @param size Number of bytes to read, at maximum.
     * @param offset Offset inside the file to start reading.
     * @return Number of bytes read on success, Error on failure.
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

    /**
     * Send UDP data
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

    bool operator == (const UDPSocket & sock) const
    {
        return true;
    }
    bool operator != (const UDPSocket & sock) const
    {
        return false;
    }

  private:

    /** UDP protocol instance */
    UDP *m_udp;

    /** Local port */
    u16 m_port;

    /** Incoming packet queue */
    NetworkQueue m_queue;
};

#endif /* __LIBNET_UDPSOCKET_H */
