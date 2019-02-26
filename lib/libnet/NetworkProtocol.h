#ifndef __LIBNET_NETWORKPROTOCOL_H
#define __LIBNET_NETWORKPROTOCOL_H

#include <Directory.h>
#include <Types.h>
#include "NetworkQueue.h"

class NetworkServer;
class NetworkDevice;

/**
 * Network protocol abstraction class.
 */
class NetworkProtocol : public Directory
{
  public:

    /**
     * Constructor
     */
    NetworkProtocol(NetworkServer *server,
                    NetworkDevice *device);

    /**
     * Destructor
     */
    virtual ~NetworkProtocol();


    /**
     * Get maximum packet size.
     *
     * @return Packet size in bytes
     */
    virtual const Size getMaximumPacketSize() const;

    /**
     * Perform initialization.
     */
    virtual Error initialize() = 0;

    /**
     * Process incoming network packet.
     *
     * @return Error code
     */
    virtual Error process(NetworkQueue::Packet *pkt, Size offset) = 0;

  protected:

    /** Network server instance */
    NetworkServer *m_server;

    /** Network device instance */
    NetworkDevice *m_device;
};

#endif /* __LIBNET_NETWORKPROTOCOL_H */
