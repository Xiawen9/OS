#ifndef __BIN_NETCAT_H
#define __BIN_NETCAT_H

#include <IPV4.h>
#include <Ethernet.h>
#include <NetworkClient.h>
#include <POSIXApplication.h>

/**
 * Network send/receive (cat) application.
 */
class NetCat : public POSIXApplication
{
  public:

    /**
     * Class constructor.
     */
    NetCat(int argc, char **argv);

    /**
     * Class destructor.
     */
    virtual ~NetCat();

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
     * Read one line from standard input.
     */
    Result readLine();

    /**
     * Send UDP packet
     */
    Result udpSend();

    Result udpReceive();

    Result printLine();

    /** Networking client */
    NetworkClient *m_client;

    /** Socket */
    int m_socket;

    /** Line buffer */
    char m_lineBuf[64];
    Size m_lineLen;

    /** Host IP */
    IPV4::Address m_host;

    /** Host port */
    u16 m_port;
};

#endif /* __BIN_NETCAT_H */
