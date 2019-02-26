/**
 * Logging utilities and definitions.
 *
 *  */

#ifndef __HOST__
#include <System.h>
#include "KernelLog.h"

KernelLog::KernelLog() : Log()
{
}

void KernelLog::write(const char *str)
{
    PrivExec(WriteConsole, (Address) str);
}

#endif /* __HOST__ */
