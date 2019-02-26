#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <NetworkClient.h>
#include <sys/socket.h>
#include <errno.h>

extern C int recvfrom(int sockfd, void *buf, size_t len, int flags,
                      struct sockaddr *addr, socklen_t addrlen)
{

    char packet[2048];
    NetworkClient::SocketInfo info;

    if (len > sizeof(packet) - addrlen)
        return ERANGE;

    Error r = ::read(sockfd, packet, sizeof(packet));
    if (r < 0)
        return r;

    // TODO: inefficient. and move to NetworkClient.
    addr->addr = info.address;
    addr->port = info.port;
    memcpy(buf, packet + sizeof(info), r - sizeof(info));
    return r - sizeof(info);
}
