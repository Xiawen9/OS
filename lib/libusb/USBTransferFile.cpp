#include <Log.h>
#include "USBMessage.h"
#include "USBTransferFile.h"
#include "USBDescriptor.h"

USBTransferFile::USBTransferFile(USBController *controller)
    : File()
{
    m_access     = OwnerRW;
    m_controller = controller;
}

Error USBTransferFile::write(IOBuffer & buffer, Size size, Size offset)
{
    //DEBUG("");

    USBMessage *usb = (USBMessage *) buffer.getBuffer();
    const FileSystemMessage *msg = buffer.getMessage();

    if (size != sizeof(USBMessage))
    {
        ERROR("invalid size " << size << " != sizeof(USBMessage)");
        return EIO;
    }

    switch (usb->state)
    {
        case USBMessage::Setup:
        case USBMessage::Data:
        case USBMessage::Status:
            return m_controller->transfer(msg, usb);

        case USBMessage::Success:
            buffer.write((void *)buffer.getBuffer(), sizeof(*usb));
            return size;

        case USBMessage::Failure:
            return EIO;

        default:
            ERROR("invalid unknown USBMessage state: " << (int) usb->state);
            break;
    }
    return EIO;
}
