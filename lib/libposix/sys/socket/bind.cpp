#include <sys/socket.h>
#include <errno.h>

extern C int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    // write to $device/$proto/socket file and receive path to the actual file.
    // then replace fd with this one
    return ENOTSUP;
}
