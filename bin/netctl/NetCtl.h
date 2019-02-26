#ifndef __BIN_NETPING_H
#define __BIN_NETPING_H

#include <IPV4.h>
#include <Ethernet.h>
#include <POSIXApplication.h>

/**
 * Network interface control application.
 */
class NetCtl : public POSIXApplication
{
  public:

    /**
     * Class constructor.
     */
    NetCtl(int argc, char **argv);

    /**
     * Class destructor.
     */
    virtual ~NetCtl();

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
     * Output device information
     *
     * @param deviceName Name of the network device
     * @return Result code
     */
    Result showDevice(const char *deviceName);

};

#endif /* __BIN_NETCTL_H */
