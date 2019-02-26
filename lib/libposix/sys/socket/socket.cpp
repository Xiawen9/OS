#include <NetworkClient.h>
#include <sys/socket.h>
#include <errno.h>

extern C int socket(int domain, int type, int protocol)
{
    NetworkClient client("");
    int sock;

    // This opens /network/$device/$protocol/socket
    //
    // The bind() function will then write 0+address+port to that socket file, ( or 'b'+address+port)
    // and read from it to receive the path to the actual file for the new socket,
    // and replaces this fd with that file.
    //
    // connect() does similar, but it will write 1+address+port to that socket file, ( or 'l' + address+port)
    // and read to get the path to the new socket file and replaces the fd.
    client.initialize();

    if (domain == AF_INET && type == SOCK_DGRAM && protocol == IPPROTO_ICMP)
    {
        if (client.createSocket(NetworkClient::ICMP, &sock) == NetworkClient::Success)
            return ESUCCESS;
        else
            return EINVAL;
    }
    return ENOTSUP;
}
