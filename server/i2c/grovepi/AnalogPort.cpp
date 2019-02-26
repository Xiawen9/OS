#include <Log.h>
#include <stdio.h>
#include "AnalogPort.h"

AnalogPort::AnalogPort(I2C *i2c, uint port)
    : Device(CharacterDeviceFile)
{
    m_i2c  = i2c;
    m_port = port;
    m_identifier << "analog" << port;
}

Error AnalogPort::initialize()
{
    return ESUCCESS;
}

Error AnalogPort::read(IOBuffer & buffer, Size size, Size offset)
{
    u8 command[4];
    char tmp[16];
    int n;

    if (offset >= 1)
        return 0;

    DEBUG("port =" << m_port);

    // Send a AnalogRead command to the GrovePi
    // including the port number and Analog value (HIGH/LOW)
    command[0] = 3;
    command[1] = m_port;
    command[2] = 0;
    command[3] = 0;
    m_i2c->setAddress(0x4);
    m_i2c->write(command, sizeof(command));
    m_i2c->read(command, 4);

    uint value = command[1] * 256 + command[2];
    n = snprintf(tmp, sizeof(tmp), "%10d", value);
    buffer.write(tmp, n);
    return n;
}
