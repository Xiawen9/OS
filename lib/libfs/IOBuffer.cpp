#include "IOBuffer.h"

IOBuffer::IOBuffer(const FileSystemMessage *msg)
    : m_message(msg)
{
    // TODO: hack because only read/write file actions need the buffer.
    if (msg->action == ReadFile || msg->action == WriteFile)
        m_buffer = new u8[msg->size];
    else
        m_buffer = 0;

    m_size   = msg->size;
    m_count  = 0;
}

IOBuffer::~IOBuffer()
{
    if (m_buffer)
        delete m_buffer;
}

Size IOBuffer::getCount() const
{
    return m_count;
}

const FileSystemMessage * IOBuffer::getMessage() const
{
    return m_message;
}

const u8 * IOBuffer::getBuffer() const
{
    return m_buffer;
}

Error IOBuffer::bufferedRead()
{
    m_count = read(m_buffer, m_message->size, 0);
    return m_count;
}

Error IOBuffer::bufferedWrite(void *buffer, Size size)
{
    Size i = 0;

    // TODO: hack. see above.
    if (!m_buffer)
        m_buffer = new u8[m_message->size];

    for (i = 0; i < size && m_count < m_size; i++)
    {
        m_buffer[m_count++] = ((u8 *)buffer)[i];
    }
    return i;
}
    
Error IOBuffer::read(void *buffer, Size size, Size offset) const
{
    return VMCopy(m_message->from, API::Read,
                 (Address) buffer,
                 (Address) m_message->buffer + offset, size);
}

Error IOBuffer::write(void *buffer, Size size, Size offset) const
{
    return VMCopy(m_message->from, API::Write,
                 (Address) buffer,
                 (Address) m_message->buffer + offset, size);
}

Error IOBuffer::flush()
{
    return write(m_buffer, m_count, 0);
}

u8 IOBuffer::operator[](Size index)
{
    return index < m_size ? m_buffer[index] : 0;
}
