#ifndef __BIN_NETSEND_H
#define __BIN_NETSEND_H

#include <IPV4.h>
#include <Ethernet.h>
#include <POSIXApplication.h>

/**
 * Network send application.
 */
class NetSend : public POSIXApplication
{
  public:

    /**
     * Class constructor.
     */
    NetSend(int argc, char **argv);

    /**
     * Class destructor.
     */
    virtual ~NetSend();

    /**
     * Initialize the application.
     */
    virtual Result initialize();

    /**
     * Execute the application event loop.
     */
    virtual Result exec();

  private:

    /**
     * Send ARP request.
     */
    Result arpRequest(IPV4::Address ipAddr, Ethernet::Address *ethAddr);

    /** Socket */
    int m_socket;
};

#endif /* __BIN_NETSEND_H */
