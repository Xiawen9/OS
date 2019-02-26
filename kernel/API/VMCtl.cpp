#include <System.h>
#include <SplitAllocator.h>
#include "VMCtl.h"
#include "ProcessID.h"

Error VMCtlHandler(ProcessID procID, MemoryOperation op, Memory::Range *range)
{
    ProcessManager *procs = Kernel::instance->getProcessManager();
    Process *proc = ZERO;
    Error ret = API::Success;

    DEBUG("");
    
    // Find the given process
    if (procID == SELF)
        proc = procs->current();
    else if (!(proc = procs->get(procID)))
    {
        return API::NotFound;
    }

    // TODO: capability checking.
    MemoryContext *mem = proc->getMemoryContext();

    // Perform operation
    switch (op)
    {
        case LookupVirtual:
            if (mem->lookup(range->virt, &range->phys) != MemoryContext::Success)
                return API::AccessViolation;
            break;

        case Map:
            if (!range->virt)
            {
                mem->findFree(range->size, MemoryMap::UserPrivate, &range->virt);
                range->virt += range->phys & ~PAGEMASK;
            }
            mem->mapRange(range);
            break;

        case UnMap:
            mem->unmapRange(range);
            break;

        case Release:
            mem->releaseRange(range);
            break;

        case CacheClean: {
            Arch::Cache cache;
            cache.cleanInvalidate(Cache::Data);
            break;
        }
        case Access:
            ret = (API::Error) mem->access(range->virt, &range->access);
            break;

        case RemoveMem:
#warning TODO: claiming memory should be atomic single shot call.
            for (uint i = 0; i < range->size; i+=PAGESIZE)
            {
                if (Kernel::instance->getAllocator()->allocate(range->phys + i) != Allocator::Success)
                {
                    ERROR("address " << (void *) (range->phys + i) << " already allocated");
                    return API::OutOfMemory;
                }
            }
            break;

        default:
            ret = API::InvalidArgument;
            break;
    }
    // Done
    return ret;
}
