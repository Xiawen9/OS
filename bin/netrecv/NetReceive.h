#ifndef __BIN_NETRECEIVE_H
#define __BIN_NETRECEIVE_H

#include <IPV4.h>
#include <Ethernet.h>
#include <POSIXApplication.h>

/**
 * Network receive application.
 */
class NetReceive : public POSIXApplication
{
  public:

    /**
     * Class constructor.
     */
    NetReceive(int argc, char **argv);

    /**
     * Class destructor.
     */
    virtual ~NetReceive();

    /**
     * Initialize the application.
     */
    virtual Result initialize();

    /**
     * Execute the application event loop.
     */
    virtual Result exec();

  private:

    Result receiveArp();
    Result receivePacket(u8 *packet, Size size);

    /** Socket */
    int m_socket;
};

#endif /* __BIN_NETRECEIVE_H */
