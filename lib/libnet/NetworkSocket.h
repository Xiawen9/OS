#ifndef __LIBNET_NETWORKSOCKET_H
#define __LIBNET_NETWORKSOCKET_H

#include <File.h>
#include <Types.h>
#include "NetworkQueue.h"
#include "NetworkClient.h"

/**
 * Network socket represents a single logical connection on a protocol.
 */
class NetworkSocket : public File
{
  public:

    /**
     * Constructor
     *
     * @param packetSize Size of each network packet
     */
    NetworkSocket(Size packetSize);

    /**
     * Destructor
     */
    virtual ~NetworkSocket();

    /**
     * Process incoming network packet.
     *
     * @return Error code
     */
    virtual Error process(NetworkQueue::Packet *pkt) = 0;

  protected:

    /** Process which owns the socket */
    ProcessID m_pid;

    /** Receive queue */
    NetworkQueue m_receive;

    /** Transmit queue */
    NetworkQueue m_transmit;

    /** Socket connection */
    NetworkClient::SocketInfo m_info;
};

#endif /* __LIBNET_NETWORKSOCKET_H */
