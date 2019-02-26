#ifndef __API_VMCTL_H
#define __API_VMCTL_H

#include <System.h>

/**  
 * @defgroup kernelapi kernel (API) 
 * @{  
 */

/**
 * Memory operations which may be used as an argument to VMCtl().
 */
typedef enum MemoryOperation
{
    Map = 0,
    UnMap,
    Release,
    LookupVirtual,
    Access,
    RemoveMem,
    AddMem,
    CacheClean
}
MemoryOperation;

/**
 * Prototype for user applications. Examines and modifies virtual memory pages.
 * @param procID Remote process.
 * @param op Determines which operation to perform.
 * @param range Describes the memory pages to operate on.
 * @return Zero on success or error code on failure.
 */
inline Error VMCtl(ProcessID procID, MemoryOperation op,
                   Memory::Range *range = ZERO)
{
    return trapKernel3(API::VMCtlNumber, procID, op, (Address) range);
}

extern Error VMCtlHandler(ProcessID procID, MemoryOperation op, Memory::Range *range);

/**
 * @}
 */

#endif /* __API_VMCTL_H */
