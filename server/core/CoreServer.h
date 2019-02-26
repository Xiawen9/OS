#ifndef __CORE_CORESERVER_H
#define __CORE_CORESERVER_H

/**
 * @defgroup core CoreServer
 * @{  
 */

#include <System.h>
#include <API.h>
#include <ChannelServer.h>
#include <List.h>
#include <ListIterator.h>
#include <String.h>
#include <Types.h>
#include <Macros.h>
#include <Index.h>
#include <ExecutableFormat.h>
#include <MemoryChannel.h>
#include <FileSystemMessage.h>
#include <CoreInfo.h>

#ifdef INTEL
#include <intel/IntelMP.h>
#include <intel/IntelACPI.h>
#endif /* INTEL */

/**
 * Represents a single Core in a Central Processing Unit (CPU).
 *
 * Each core in a system will run its own instance of CoreServer.
 * CoreServers will communicate and collaborate together to implement functionality.
 */
class CoreServer : public ChannelServer<CoreServer, FileSystemMessage>
{
  private:

    /** The default kernel for starting new cores. */
    static const char *kernelPath;

  public:

    /**
     * Result codes.
     */    
    enum Result
    {
        Success,
        NotFound,
        BootError,
        ExecError,
        OutOfMemory,
        IOError,
        MemoryError
    };

    /**
     * Class constructor function.
     */
    CoreServer();

    Result initialize();

    Result bootCore(uint coreId, CoreInfo *info, ExecutableFormat::Region *regions);

    Result discover();

    Result loadKernel();

    Result bootAll();

    Result test();

    int runCore();

    bool retryRequests();

  private:

    Result setupChannels();

    Result clearPages(Address addr, Size size);

    void getCoreCount(FileSystemMessage *msg);

    void createProcess(FileSystemMessage *msg);

#ifdef INTEL
    IntelMP m_mp;
    IntelACPI m_acpi;
    CoreManager *m_cores;
#endif /* INTEL */

    ExecutableFormat *m_kernel;
    u8 *m_kernelImage;

    ExecutableFormat::Region m_regions[16]; 

    Size m_numRegions;

    Index<CoreInfo> *m_coreInfo;
    SystemInformation m_info;

    Index<MemoryChannel> *m_fromSlave;
    Index<MemoryChannel> *m_toSlave;

    MemoryChannel *m_toMaster;
    MemoryChannel *m_fromMaster;
};

/**
 * @}
 */

#endif /* __CORE_CORESERVER_H */
