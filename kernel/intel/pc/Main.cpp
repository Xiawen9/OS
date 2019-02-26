#include <Support.h>
#include <Config.h>
#include <System.h>
#include <intel/IntelKernel.h>
#include <intel/IntelSerial.h>
#include <CoreInfo.h>
#include <Macros.h>
#include <Log.h>

extern C int kernel_main(CoreInfo *info)
{
    // Initialize heap at 3MB offset
    // TODO: fix this
    Kernel::heap( MegaByte(3),
                  MegaByte(1) );

    // Start kernel debug serial console
    // TODO: can I re-use the user-land driver here somehow????
    if (info->coreId == 0)
    {
        IntelSerial *serial = new IntelSerial(0x3f8);
        serial->setMinimumLogLevel(Log::Notice);
    }

    // TODO: put this in the boot.S, or maybe hide it in the support library? maybe a _run_main() or something.
    constructors();

    // Create and run the kernel
    IntelKernel *kernel = new IntelKernel(info);
    return kernel->run();
}
