#ifndef __SERVER_I2C_GROVEPI_LCDBAR_H
#define __SERVER_I2C_GROVEPI_LCDBAR_H

/**     
 * @defgroup groveDigi GrovePi LCD Bar
 * @{
 */

#include <Macros.h>
#include <Types.h>
#include <Device.h>
#include <I2C.h>

/**
 * @brief GrovePi LCD Bar
 *
 * @see https://github.com/DexterInd/GrovePi/blob/master/Firmware/Source/v1.2/grove_pi_v1_2_5/README.md
 */
class LCDBar : public Device
{
  private:

    static const uint RGBAddr  = 0x62;
    static const uint TextAddr = 0x3e;

    /**
     * LCDBar commands.
     */
    enum Command
    {
        ClearDisplay = 0x01,
        NoCursor     = 0x04,
        DisplayOn    = 0x08,
        DoubleLine   = 0x28,
        Newline      = 0xc0,
        WriteChar    = 0x40
    };

  public:

    /**
     * @brief Constructor function.
     */
    LCDBar(I2C *i2c);

    /**
     * @brief Initializes the class.
     *
     * @return Error status code.
     */
    virtual Error initialize();

    /** 
     * @brief Set LCD Bar text.
     *
     * @param buffer Buffer to save the read bytes.
     * @param size Number of bytes to read.
     * @param offset Offset in the file to read.
     * @return Number of bytes on success and ZERO on failure. 
     */
    virtual Error write(IOBuffer & buffer, Size size, Size offset);

  private:

    /**
     * Set LCD color.
     */
    void setRGB(uint r, uint g, uint b);

    /**
     * Set LCD text.
     */
    void setText(const char *text, Size max);

    /**
     * Send I2C text command.
     */
    void textCommand(Command cmd);

    /** I2C controller */
    I2C *m_i2c;
};

/**
 * @}
 */

#endif /* __TIME_TIME_H */
