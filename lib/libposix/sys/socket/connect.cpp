#include <NetworkClient.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

extern C int connect(int sockfd, struct sockaddr *addr, socklen_t addrlen)
{
    NetworkClient client("");
    client.initialize();
    if (client.connectSocket(sockfd, addr->addr) == NetworkClient::Success)
        return ESUCCESS;
    else
        return EIO;
}
