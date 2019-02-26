#ifndef __LIBNET_NETWORKSERVER_H
#define __LIBNET_NETWORKSERVER_H

#include <Types.h>
#include <DeviceServer.h>
#include "NetworkDevice.h"
#include "Ethernet.h"
#include "IPV4.h"

/**
 * Networking server.
 */
class NetworkServer : public DeviceServer
{
  public:

    /**
     * Constructor
     */
    NetworkServer(const char *path);

    /**
     * Destructor
     */
    virtual ~NetworkServer();

    /**
     * Initialize the NetworkServer.
     */
    virtual Error initialize();
};

#endif /* __LIBNET_NETWORKSERVER_H */
