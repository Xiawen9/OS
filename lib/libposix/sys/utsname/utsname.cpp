#include <Config.h>
#include <string.h>
#include "unistd.h"
#include "sys/utsname.h"

int uname(struct utsname *name)
{
    /* Fill in the struct. */
    strlcpy(name->sysname, "OS", UTSBUF);
    gethostname(name->nodename, UTSBUF);
    /* Success. */
    return 0;
}
