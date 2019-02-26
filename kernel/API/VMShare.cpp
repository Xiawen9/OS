#include <System.h>
#include <ProcessEvent.h>
#include <MemoryBlock.h>
#include "VMShare.h"
#include "ProcessID.h"

Error VMShareHandler(ProcessID procID, API::Operation op, ProcessShares::MemoryShare *share)
{
    // TODO: use the share.range.physicalAddress as identifier? its unique.
    ProcessManager *procs = Kernel::instance->getProcessManager();
    Process *proc = ZERO;
    Error ret = API::Success;

    DEBUG("");
    
    // Find the given process
    if (procID == SELF)
    {
        if (op != API::Read)
            return API::InvalidArgument;
        else
            proc = procs->current();
    }
    else if (!(proc = procs->get(procID)) && op != API::Delete)
    {
        return API::NotFound;
    }

    switch (op)
    {
        case API::Create:
        {
            switch (procs->current()->getShares().createShare(proc->getShares(), share))
            {
                case ProcessShares::Success: return API::Success;
                case ProcessShares::AlreadyExists: return API::AlreadyExists;
                default: return API::IOError;
            }
            break;
        }
        case API::Read:
            if (procs->current()->getShares().readShare(share) != ProcessShares::Success)
            {
                ret = API::IOError;
            }
            break;

        case API::Delete:
            if (procs->current()->getShares().removeShares(procID) != ProcessShares::Success)
                ret = API::IOError;
            break;

        default:
            return API::InvalidArgument;
    }

    // Done
    return ret;
}
