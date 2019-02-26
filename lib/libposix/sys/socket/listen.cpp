#include <sys/socket.h>
#include <errno.h>

extern C int listen(int sockfd, int backlog)
{
    // does nothing really. bind() is already done enough
    return ENOTSUP;
}
