#ifndef __API_PRIVEXEC_H
#define __API_PRIVEXEC_H

#include <System.h>

/**  
 * @defgroup kernelapi kernel (API) 
 * @{  
 */

/**
 * Available operations to perform using PrivExec().
 * @see PrivExec
 */
typedef enum PrivOperation
{
    Idle         = 0,
    Reboot       = 1,
    Shutdown     = 2,
    WriteConsole = 3
}
PrivOperation;

/**
 * Prototype for user applications. Performs various privileged operations.
 * @param op The operation to perform.
 * @return Zero on success and error code on failure.
 */
inline Error PrivExec(PrivOperation op, Address param = 0)
{
    return trapKernel2(API::PrivExecNumber, op, param);
}

/**
 * Prototype for kernel handler.
 */
extern Error PrivExecHandler(PrivOperation op, Address param);

/**
 * @}
 */

#endif /* __API_PRIVEXEC_H */
