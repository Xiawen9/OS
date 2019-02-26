#include <System.h>
#include "unistd.h"

pid_t getpid()
{
    return ProcessCtl(SELF, GetPID);
}
