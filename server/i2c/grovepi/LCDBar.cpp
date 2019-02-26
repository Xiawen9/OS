#include <unistd.h>
#include "LCDBar.h"

LCDBar::LCDBar(I2C *i2c)
    : Device(CharacterDeviceFile)
{
    m_i2c = i2c;
    m_identifier << "lcd";
}

Error LCDBar::initialize()
{
    return ESUCCESS;
}

Error LCDBar::write(IOBuffer & buffer, Size size, Size offset)
{
    setRGB(0, 255, 0);
    setText((const char *) buffer.getBuffer(), size);
    return size;
}

void LCDBar::textCommand(LCDBar::Command cmd)
{
    u8 command[2];

    command[0] = 0x80;
    command[1] = cmd;

    m_i2c->setAddress(TextAddr);
    m_i2c->write(command, sizeof(command));
}

void LCDBar::setText(const char *text, Size max)
{
    textCommand(ClearDisplay);
    sleep(1);

    textCommand(DisplayOn | NoCursor);
    textCommand(DoubleLine);
    sleep(1);

    for (uint line = 0; line < 2; line++)
    {
        for (uint i = 0; i < 16; i++)
        {
            if (i + (line * 16) >= max)
                return;

            char v = text[i + (line * 16)];

            if (!v)
                return;
            else if (v == '\n')
            {
                textCommand(Newline);
                break;
            }
            else
            {
                u8 command[2];
                command[0] = 0x40;
                command[1] = v;
                m_i2c->write(command, sizeof(command));
            }
        }
    }
}

void LCDBar::setRGB(uint r, uint g, uint b)
{
    u8 command[2];
    command[0] = 0;
    command[1] = 0;
    m_i2c->setAddress(0x62);
    m_i2c->write(command, sizeof(command)); // 0,0

    command[0] = 1;
    m_i2c->write(command, sizeof(command)); // 1,0

    command[0] = 0x8;
    command[1] = 0xaa;
    m_i2c->write(command, sizeof(command)); // 0x08,0xaa

    command[0] = 4;
    command[1] = r;
    m_i2c->write(command, sizeof(command)); // 4,r

    command[0] = 3;
    command[1] = g;
    m_i2c->write(command, sizeof(command)); // 3,g

    command[0] = 2;
    command[1] = b;
    m_i2c->write(command, sizeof(command)); // 2,b
}
