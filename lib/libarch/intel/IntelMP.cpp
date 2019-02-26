#include <System.h>
#include <Log.h>
#include "IntelConstant.h"
#include "IntelMP.h"
#include "IntelBoot.h"

IntelMP::IntelMP()
    : CoreManager()
{
    SystemInformation info;

    m_bios.map(MPAreaAddr, MPAreaSize);
    m_lastMemory.map(info.memorySize - MegaByte(1), MegaByte(1));

    // TODO: avoid this. just pass a initialize(bool hardwareReset = true/false) instead
    m_apic.getIO().map(IntelAPIC::IOBase, PAGESIZE);
}

IntelMP::MPConfig * IntelMP::scanMemory(Address addr)
{
    MPFloat *mpf;

    // Look for the Multiprocessor configuration
    for (uint i = 0; i < MPAreaSize - sizeof(Address); i += sizeof(Address))
    {
        mpf = (MPFloat *)(addr + i);

        if (mpf->signature == MPFloatSignature)
            return (MPConfig *) (mpf->configAddr - MPAreaAddr + addr);
    }
    return ZERO;
}

IntelMP::Result IntelMP::discover()
{
    MPConfig *mpc = 0;
    MPEntry *entry;

    // Clear previous discoveries
    m_cores.clear();

    // Try to find MPTable in the BIOS memory.
    mpc = scanMemory(m_bios.getBase());

    // Retry in the last 1MB of physical memory if not found.
    if (!mpc)
    {
        mpc = scanMemory(m_lastMemory.getBase());
        if (!mpc)
        {
            ERROR("MP header not found");
            return NotFound;
        }
    }

    // Found config
    DEBUG("MP header found at " << (void *) mpc);
    DEBUG("Local APIC at " << (void *) mpc->apicAddr);
    entry = (MPEntry *)(mpc + 1);

    // Search for multiprocessor entries
    for (uint i = 0; i < mpc->count; i++)
        entry = parseEntry(entry);

    return Success;
}

IntelMP::Result IntelMP::boot(CoreInfo *info)
{
    DEBUG("booting core" << info->coreId << " at " <<
            (void *) info->memory.phys << " with kernel: " << info->kernelCommand);

    // TODO: load the kernel, reserve memory, etc
    // TODO: upper layer should have loaded the kernel in memory already.

    // Copy 16-bit realmode startup code
    // TODO: place this in the kernel binary somewhere instead?
    VMCopy(SELF, API::Write, (Address) bootEntry16, MPEntryAddr, PAGESIZE);

    // Copy the CoreInfo structure
    VMCopy(SELF, API::Write, (Address) info, MPInfoAddr, sizeof(*info));

    // Send inter-processor-interrupt to wakeup the processor
    if (m_apic.sendStartupIPI(info->coreId, MPEntryAddr) != IntController::Success)
        return IOError;

    // Wait until the core raises the 'booted' flag in CoreInfo
    // TODO: set somekind of limit to wait???
    while (1)
    {
        CoreInfo check;

        VMCopy(SELF, API::Read, (Address) &check, MPInfoAddr, sizeof(check));

        if (check.booted)
            break;
    }
    return Success;
}

IntelMP::MPEntry * IntelMP::parseEntry(IntelMP::MPEntry *entry)
{
    if (entry->type == MPEntryProc)
    {
        m_cores.append(entry->apicId);
        return entry + 1;
    }
    else
        return (MPEntry *) (((Address)(entry)) + 8);
}
