#include <Log.h>
#include "DigitalPort.h"

DigitalPort::DigitalPort(I2C *i2c, uint port)
    : Device(CharacterDeviceFile)
{
    m_i2c  = i2c;
    m_port = port;
    m_identifier << "digital" << port;
}

Error DigitalPort::initialize()
{
    return ESUCCESS;
}

Error DigitalPort::read(IOBuffer & buffer, Size size, Size offset)
{
    u8 command[4];
    char result[2];

    if (offset >= 1)
        return 0;

    DEBUG("port =" << m_port);

    // Send a digitalRead command to the GrovePi
    // including the port number and digital value (HIGH/LOW)
    command[0] = 1;
    command[1] = m_port;
    command[2] = 0;
    command[3] = 0;
    m_i2c->setAddress(0x4);
    m_i2c->write(command, sizeof(command));
    m_i2c->read(command, 1);

    result[0] = '0' + command[0];
    result[1] = 0;
    buffer.write(result, 1);

    // Done
    return 1;
}

Error DigitalPort::write(IOBuffer & buffer, Size size, Size offset)
{
    u8 command[4];

    for (Size i = 0; i < size; i++)
    {
        DEBUG("buffer[" << i << "] =" << buffer[i]);
    }
    DEBUG("port =" << m_port);

    // Send a digitalWrite command to the GrovePi
    // including the port number and digital value (HIGH/LOW)
    command[0] = 2;
    command[1] = m_port;
    command[2] = buffer[0] != '0';
    command[3] = 0;
    m_i2c->setAddress(0x4);
    m_i2c->write(command, sizeof(command));

    // Done
    return size;
}
