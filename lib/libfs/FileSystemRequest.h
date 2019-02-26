#ifndef __FILESYSTEM_FILE_SYSTEM_REQUEST_H
#define __FILESYSTEM_FILE_SYSTEM_REQUEST_H

#include "FileSystemMessage.h"
#include "IOBuffer.h"

/**
 * Encapsulates a pending FileSystemMessage.
 */
class FileSystemRequest
{
  public:

    /**
     * Constructor
     */
    FileSystemRequest(FileSystemMessage *msg);

    /**
     * Destructor
     */
    virtual ~FileSystemRequest();

    /**
     * Get message.
     */
    FileSystemMessage * getMessage();

    /**
     * Get IOBuffer.
     */
    IOBuffer & getBuffer();

  private:

    /** Message that was received */
    FileSystemMessage m_msg;

    /** Wrapper for doing I/O on the FileSystemMessage buffer. */
    IOBuffer *m_ioBuffer;
};

#endif /* __FILESYSTEM_FILE_SYSTEM_REQUEST_H */
