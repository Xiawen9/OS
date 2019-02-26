#ifndef __LIBPOSIX_TIME_H
#define __LIBPOSIX_TIME_H

#include <Macros.h>
#include "types.h"

/**                                                                                                                                                                                                     
 * @defgroup libposix libposix (POSIX.1-2008)
 * @{
 */ 

/**
 * Time value information.
 */
struct timeval
{
    /** Seconds */
    time_t tv_sec;

    /** Microseconds */
    uint   tv_usec;
};

/**
 * Time zone information.
 */
struct timezone
{
    /** minutes west of Greenwich */
    int tz_minuteswest;
    
    /** type of DST correction */
    int tz_dsttime;
};

/**
 * Get current time of day.
 *
 * @param tv Timeval struct object pointer.
 * @param tz Timezone struct object pointer.
 * @return Zero on success and -1 on error.
 */
extern C int gettimeofday(struct timeval *tv, struct timezone *tz);

/**
 * Print time difference.
 *
 * @param t1 First timeval struct.
 * @param t2 Second timeval struct.
 * @return Zero on success or -1 on failure.
 */
extern C int printtimediff(struct timeval *t1, struct timeval *t2);

/**
 * @}
 */

#endif /* __LIBPOSIX_TIME_H */
