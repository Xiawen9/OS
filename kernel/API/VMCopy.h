#ifndef __API_VMCOPY_H
#define __API_VMCOPY_H

#include <System.h>

/**  
 * @defgroup kernelapi kernel (API) 
 * @{  
 */

/**
 * Prototype for user applications. Copies virtual memory between two processes.
 * @param proc Remote process.
 * @param how Read or Write.
 * @param ours Virtual address of the buffer of this process.
 * @param theirs Virtual address of the remote process' buffer.
 * @param sz Amount of memory to copy.
 * @return Total number of bytes copied on success and error code on failure.
 */
inline Error VMCopy(ProcessID proc, API::Operation how, Address ours,
                         Address theirs, Size sz)
{
    return trapKernel5(API::VMCopyNumber, proc, how, ours, theirs, sz);
}

extern Error VMCopyHandler(ProcessID proc, API::Operation how, Address ours, Address theirs, Size sz);

/**
 * @}
 */

#endif /* __API_VMCOPY_H */
