#include <System.h>
#include "unistd.h"

pid_t getppid()
{
    return ProcessCtl(SELF, GetParent);
}
