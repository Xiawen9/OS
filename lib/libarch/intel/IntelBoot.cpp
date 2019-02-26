#include <String.h>
#include <MemoryBlock.h>
#include <CoreInfo.h>
#include "IntelBoot.h"

void multibootToCoreInfo(MultibootInfo *info)
{
    // Fill coreId and memory info
    MemoryBlock::set(&coreInfo, 0, sizeof(CoreInfo));
    coreInfo.coreId = 0;
    coreInfo.kernel.phys = 0;
    coreInfo.kernel.size = MegaByte(4);
    coreInfo.memory.phys = 0;
    coreInfo.memory.size = (info->memUpper * 1024) + MegaByte(1);

    // Fill the kernel command line
    MemoryBlock::copy(coreInfo.kernelCommand, (void *)info->cmdline, KERNEL_PATHLEN);

    // Fill the bootimage address
    for (Size n = 0; n < info->modsCount; n++)
    {
        MultibootModule *mod = (MultibootModule *) info->modsAddress;
        mod += n;
        String str((char *)(mod->string), false);

        // Is this the BootImage?
        if (str.match("*.img.gz"))
        {
            coreInfo.bootImageAddress = mod->modStart;
            coreInfo.bootImageSize    = mod->modEnd - mod->modStart;
            break;
        }
    }
}
