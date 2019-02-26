#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>
#include <Types.h>

int printtimediff(struct timeval *t1, struct timeval *t2)
{
    u64 usec1 = (t1->tv_sec * 1000000) + (t1->tv_usec);
    u64 usec2 = (t2->tv_sec * 1000000) + (t2->tv_usec);

    // Print time measured
    printf("%us %uusec",
            (uint) ((usec2 - usec1) / 1000000),
            (uint) ((usec2 - usec1) % 1000000));
    return 0;
}
