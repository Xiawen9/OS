#ifndef __LIBPOSIX_TIME_H
#define __LIBPOSIX_TIME_H

#include <Macros.h>
#include "sys/types.h"

/**                                                                                                                                                                                                     
 * @defgroup libposix libposix (POSIX.1-2008)
 * @{
 */ 

/**
 * The <time.h> header shall declare the timespec structure.
 */
struct timespec
{
    /** Seconds. */
    time_t tv_sec;
    
    /** Nanoseconds. */
    long tv_nsec;
};

extern unsigned long mktime(const unsigned int year, const unsigned int month,
                            const unsigned int day, const unsigned int hour,
                            const unsigned int min, const unsigned int sec);
/**
 * @}
 */

#endif /* __LIBPOSIX_TIME_H */
