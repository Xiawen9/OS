#include <sys/socket.h>
#include <errno.h>

extern C int shutdown(int sockfd, int how)
{
    // removes socket using DeleteFile
    return ENOTSUP;
}
