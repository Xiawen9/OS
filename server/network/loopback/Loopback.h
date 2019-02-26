#ifndef __SERVER_NETWORK_LOOPBACK_H
#define __SERVER_NETWORK_LOOPBACK_H

#include <Types.h>
#include <NetworkDevice.h>
#include <Ethernet.h>

/**
 * Loopback network device implementation.
 */
class Loopback : public NetworkDevice
{
  public:

    /**
     * Constructor
     */
    Loopback(NetworkServer *server);

    /**
     * Destructor
     */
    virtual ~Loopback();

    /**
     * Perform initialization
     */
    virtual Error initialize();

    /**
     * Read ethernet address.
     *
     * @param address Ethernet address reference for output
     * @return Error code
     */
    virtual Error getAddress(Ethernet::Address *address);

    /**
     * Set ethernet address
     *
     * @param address New ethernet address to set
     * @return Error code
     */
    virtual Error setAddress(Ethernet::Address *address);

    /**
     * Transmit one network packet
     *
     * @param pkt Network packet buffer
     */
    virtual Error transmit(NetworkQueue::Packet *pkt);

  private:

    /** Ethernet address for the loopback device */
    Ethernet::Address m_address;
};

#endif /* __SERVER_NETWORK_LOOPBACK_H */
