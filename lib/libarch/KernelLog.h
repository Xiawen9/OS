/**
 * Logging utilities and definitions.
 */

#ifndef __LIBARCH_KERNELLOG_H
#define __LIBARCH_KERNELLOG_H

#ifndef __HOST__
#include "Log.h"

/**
 * Log using PrivExec().
 */
class KernelLog : public Log
{
  public:

    /**
     * Constructor
     */
    KernelLog();

    /**
     * Write using PrivExec()
     */
    virtual void write(const char *str);
};

#endif /* __HOST__ */
#endif /* __LIBARCH_KERNELLOG_H */
