#include <unistd.h>
#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"

int vprintf(const char *format, va_list args)
{
    char buf[1024];
    Size size, written = 0;
    Error e;
    
    /* Write formatted string. */
    size = vsnprintf(buf, sizeof(buf), format, args);
    
    /* Write it to standard output. */
    while (written < size)
    {
	e = write(1, buf + written, size - written);
	
	switch (e)
	{
	    /* Error occurred. */
	    case -1:
		return e;
	
	    /* End of file reached. */
	    case 0:
		return written;
		
	    /* Process bytes. */
	    default:
		written += e;
	}
    }
    /* All done. */
    return written;
}
