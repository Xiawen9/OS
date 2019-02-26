/**
 * Logging utilities and definitions.
 *
 * */

#ifndef __HOST__
#include <System.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "StdioLog.h"

StdioLog::StdioLog() : Log()
{
}

void StdioLog::write(const char *str)
{
    ::write(1, str, strlen(str));
}

#endif /* __HOST__ */
