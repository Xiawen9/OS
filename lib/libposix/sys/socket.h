#ifndef __LIBPOSIX_SYS_SOCKET_H
#define __LIBPOSIX_SYS_SOCKET_H

#include <Macros.h>
#include "types.h"

/**                                                                                                                                                                                                     
 * @defgroup libposix libposix (POSIX.1-2008)
 * @{
 */ 

/**
 * Communication domains
 */
enum
{
    AF_INET,
    AF_INET6,
    AF_UNIX
};

/**
 * Socket types
 */
enum
{
    SOCK_STREAM,
    SOCK_DGRAM
};

/**
 * Communication Protocols
 */
enum
{
    IPPROTO_TCP,
    IPPROTO_UDP,
    IPPROTO_ICMP
};

enum
{
    SHUT_RD,
    SHUT_WR,
    SHUT_RDWR
};

struct sockaddr
{
    u32 addr;
    u16 port;
};

typedef Size socklen_t;

/**
 * Create socket endpoint for communication
 *
 * @param domain Communication domain
 * @param
 */
extern C int socket(int domain, int type, int protocol);

extern C int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/**
 * Listen for connections on a socket
 *
 * @param sockfd pid Process ID of child to wait for.
 * @param backlog Number of pending connections which can be queued.
 * @return Zero on success and -1 on error.
 */
extern C int listen(int sockfd, int backlog);

extern C int accept(int sockfd, struct sockaddr *addr, socklen_t addrlen);

extern C int connect(int sockfd, struct sockaddr *addr, socklen_t addrlen);

extern C int recvfrom(int sockfd, void *buf, size_t len, int flags,
                      struct sockaddr *addr, socklen_t addrlen);

extern C int sendto(int sockfd, const void *buf, size_t len, int flags,
                    const struct sockaddr *addr, socklen_t addrlen);

extern C int shutdown(int sockfd, int how);

/**
 * @}
 */

#endif /* __LIBPOSIX_SYS_SOCKET_H */
