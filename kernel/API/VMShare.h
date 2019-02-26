#ifndef __API_VMSHARE_H
#define __API_VMSHARE_H

#include <System.h>

/**  
 * @defgroup kernelapi kernel (API) 
 * @{  
 */

/**
 * Prototype for user applications. Creates and removes shared virtual memory mappings.
 *
 * @param op Determines which operation to perform.
 * @param pid Remote process.
 * @param parameter Parameter for the operation.
 * @param size Size parameter for the operation.
 * @return Zero on success or error code on failure.
 */
inline Error VMShare(ProcessID pid, API::Operation op, ProcessShares::MemoryShare *share)
{
    return trapKernel3(API::VMShareNumber, pid, op, (Address) share);
}

extern Error VMShareHandler(ProcessID pid, API::Operation op, ProcessShares::MemoryShare *share);

/**
 * @}
 */

#endif /* __API_VMSHARE_H */
