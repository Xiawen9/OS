#include <System.h>
#include <sys/time.h>
#include <errno.h>

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    Timer::Info timer;

    // Get current system timer info
    ProcessCtl(SELF, InfoTimer, (Address) &timer);

    // Check for a valid frequency
    if (timer.frequency == 0)
    {
        errno = ERANGE;
        return -1;
    }

    // Fill the output variables
    tv->tv_sec  = timer.ticks / timer.frequency;
    tv->tv_usec = (1000000 / timer.frequency) * (timer.ticks % timer.frequency);
    return 0;
}
