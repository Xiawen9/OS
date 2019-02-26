#ifndef __API_SYSTEMINFO_H
#define __API_SYSTEMINFO_H

#include <System.h>
#include <Config.h>
#include <Kernel.h>

/**  
 * @defgroup kernelapi kernel (API) 
 * @{  
 */

/**
 * Forward declaration.
 * @see SystemInformation
 */
struct SystemInformation;
class BitAllocator;

/**
 * Prototype for user applications. Retrieves system information.
 * @param buf Target buffer.
 */
inline Error SystemInfo(SystemInformation *info)
{
    return trapKernel1(API::SystemInfoNumber, (Address) info);
}

/**
 * Kernel prototype.
 */
extern Error SystemInfoHandler(SystemInformation *info);

/**
 * System information structure.
 */
// TODO: replace this with CoreInfo.
typedef struct SystemInformation
{
    /**
     * Constructor function.
     */
    SystemInformation()
    {
        SystemInfo(this);
    }

    /** System version. */
    ulong version;
    
    /** Boot commandline. */
    char cmdline[64];
    
    /** Total and available memory in bytes. */
    Size memorySize, memoryAvail;

    /** Core Identifier */
    uint coreId;

    /** BootImage physical address */
    Address bootImageAddress;

    /** BootImage size */
    Size bootImageSize;

    Address coreChannelAddress;
    Size coreChannelSize;

    /** Timer counter */
    uint timerCounter;
}
SystemInformation;

/**
 * @}
 */

#endif /* __API_SYSTEMINFO_H */
