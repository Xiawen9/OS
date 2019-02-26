#ifndef __BIN_NETPING_H
#define __BIN_NETPING_H

#include <IPV4.h>
#include <Ethernet.h>
#include <POSIXApplication.h>

/**
 * Network ping/pong application.
 */
class NetPing : public POSIXApplication
{
  public:

    /**
     * Class constructor.
     */
    NetPing(int argc, char **argv);

    /**
     * Class destructor.
     */
    virtual ~NetPing();

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
     * Send ARP ping/pong.
     */
    Result arpPing(const char *dev, const char *host);

    /**
     * Send ICMP ping/pong.
     */
    Result icmpPing(const char *dev, const char *host);

    /** Socket */
    int m_socket;
};

#endif /* __BIN_NETPING_H */
