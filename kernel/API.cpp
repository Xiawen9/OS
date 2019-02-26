#include <System.h>
#include <Log.h>

API::API()
{
    DEBUG("");

    // Register generic API handlers
    m_apis.fill(ZERO);
    m_apis.insert(PrivExecNumber,   (Handler *) PrivExecHandler);
    m_apis.insert(ProcessCtlNumber, (Handler *) ProcessCtlHandler);
    m_apis.insert(SystemInfoNumber, (Handler *) SystemInfoHandler);
    m_apis.insert(VMCopyNumber,     (Handler *) VMCopyHandler);
    m_apis.insert(VMCtlNumber,      (Handler *) VMCtlHandler);
    m_apis.insert(VMShareNumber,    (Handler *) VMShareHandler);
    m_apis.insert(IOCtlNumber,      (Handler *) IOCtlHandler);
}

Error API::invoke(Number number,
                  ulong arg1,
                  ulong arg2,
                  ulong arg3,
                  ulong arg4,
                  ulong arg5)
{
    Handler **handler = (Handler **) m_apis.get(number);

    if (handler)
        return (*handler)(arg1, arg2, arg3, arg4, arg5);
    else
        return InvalidArgument;
}

Log & operator << (Log &log, API::Operation op)
{
    switch (op)
    {
        case API::Create:      log.append("Create");      break;
        case API::Delete:      log.append("Delete");      break;
        case API::Send:        log.append("Send");        break;
        case API::Receive:     log.append("Receive");     break;
        case API::SendReceive: log.append("SendReceive"); break;
        case API::Read:        log.append("Read");        break;
        case API::ReadPhys:    log.append("ReadPhys");    break;
        case API::Write:       log.append("Write");       break;
    }    
    return log;
}
