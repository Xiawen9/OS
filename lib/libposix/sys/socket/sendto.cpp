#include <NetworkClient.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>

extern C int sendto(int sockfd, const void *buf, size_t len, int flags,
                    const struct sockaddr *addr, socklen_t addrlen)
{
    char packet[2048];
    NetworkClient::SocketInfo info;

    if (len > sizeof(packet) - addrlen)
        return ERANGE;

    // TODO: inefficient. and move to NetworkClient.
    info.address = addr->addr;
    info.port = addr->port;

    memcpy(packet, &info, sizeof(info));
    memcpy(packet + sizeof(info), buf, len);

    return ::write(sockfd, packet, len + sizeof(info));
}
