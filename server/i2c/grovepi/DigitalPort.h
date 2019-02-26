#ifndef __SERVER_I2C_GROVEPI_DIGITALPORT_H
#define __SERVER_I2C_GROVEPI_DIGITALPORT_H

/**     
 * @defgroup groveDigi GrovePi Digital Port
 * @{     
 */

#include <Macros.h>
#include <Types.h>
#include <Device.h>
#include <I2C.h>

/**
 * @brief GrovePi Digital Port
 *
 * @see https://github.com/DexterInd/GrovePi/blob/master/Firmware/Source/v1.2/grove_pi_v1_2_5/README.md
 */
class DigitalPort : public Device
{
  public:

    /**
     * @brief Constructor function.
     */
    DigitalPort(I2C *i2c, uint port);

    /**
     * @brief Initializes the time class.
     * @return Error status code.
     */
    virtual Error initialize();

    /**
     * @brief Read digital port value.
     *
     * @param buffer Buffer to save the read bytes.
     * @param size Number of bytes to read.
     * @param offset Offset in the file to read.
     * @return Number of bytes on success and ZERO on failure. 
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

    /** 
     * @brief Set digital port value.
     *
     * @param buffer Buffer to save the read bytes.
     * @param size Number of bytes to read.
     * @param offset Offset in the file to read.
     * @return Number of bytes on success and ZERO on failure. 
     */
    virtual Error write(IOBuffer & buffer, Size size, Size offset);

  private:

    /** I2C controller */
    I2C *m_i2c;

    /** Digital port number. */
    uint m_port;
};

/**
 * @}
 */

#endif /* __TIME_TIME_H */
