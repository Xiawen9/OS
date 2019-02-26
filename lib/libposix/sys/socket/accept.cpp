#include <sys/socket.h>
#include <errno.h>

extern C int accept(int sockfd, struct sockaddr *addr, socklen_t addrlen)
{
    // read socket which was binded to get path to the new socket, if any
    return ENOTSUP;
}
