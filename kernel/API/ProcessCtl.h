#ifndef __API_PROCESSCTL_H
#define __API_PROCESSCTL_H

#include <System.h>
#include <Process.h>
#include <Types.h>

/**  
 * @defgroup kernelapi kernel (API) 
 * @{  
 */

/**
 * Available operation to perform using ProcessCtl.
 * @see ProcessCtl
 */
typedef enum ProcessOperation
{
    Spawn = 0,
    KillPID,
    GetPID,
    GetParent,
    WatchIRQ,
    EnableIRQ,
    DisableIRQ,
    InfoPID,
    WaitPID,
    InfoTimer,
    EnterSleep,
    Schedule,
    Resume,
    SetStack
}
ProcessOperation;

/**
 * Process information structure, used for Info.
 */
typedef struct ProcessInfo
{
    /** Process Identity number. Must be unique. */
    ProcessID id;

    /** Parent process id. */
    ProcessID parent;
    
    /** Defines the current state of the Process. */
    Process::State state;
    
    /** Virtual address of the user stack. */
    Address userStack;

    /** Virtual address of the kernel stack. */
    Address kernelStack;
    
    /** Physical address of the page directory. */
    Address pageDirectory;
}
ProcessInfo;

/** Operator to print a ProcessOperation to a Log */
Log & operator << (Log &log, ProcessOperation op);

/**
 * Prototype for user applications. Process management related operations.
 *
 * @param proc Target Process' ID.
 * @param op The operation to perform.
 * @param addr Input argument address, used for program entry point for Spawn,
 *             ProcessInfo pointer for Info.
 * @param output Output argument address (optional).
 * @return Zero on success and error code on failure.
 */
inline Error ProcessCtl(ProcessID proc, ProcessOperation op, Address addr = 0, Address output = 0)
{
    return trapKernel4(API::ProcessCtlNumber, proc, op, addr, output);
}

/**
 * Kernel handler prototype.
 */
extern Error ProcessCtlHandler(ProcessID proc, ProcessOperation op, Address addr, Address output);

/**
 * @}
 */

#endif /* __API_PROCESSCTL_H */
