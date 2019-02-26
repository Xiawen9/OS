#include "USBTransferFile.h"
#include "USBController.h"

USBController::USBController(const char *path)
    : DeviceServer(path)
{
}

Error USBController::initialize()
{
    Error r = DeviceServer::initialize();

    if (r != ESUCCESS)
        return r;

    registerFile(new USBTransferFile(this), "/transfer");    
    return ESUCCESS;
}
