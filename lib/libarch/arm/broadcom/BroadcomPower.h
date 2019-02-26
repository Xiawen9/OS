#ifndef __LIBARCH_ARM_BROADCOMPOWER_H
#define __LIBARCH_ARM_BROADCOMPOWER_H

#include <Types.h>
#include <Macros.h>
#include <arm/broadcom/BroadcomMailbox.h>

/**
 * Broadcom Power Management.
 */
class BroadcomPower
{
  public:

    /**
     * Powered devices.
     */
    enum Device
    {
        SD    = (1 << 0),
        UART0 = (1 << 1),
        UART1 = (1 << 2),
        USB   = (1 << 3)
    };

    /**
     * Result codes.
     */
    enum Result
    {
        Success,
        IOError
    };

    /**
     * Constructor.
     */
    BroadcomPower();

    /**
     * Initialize the power manager.
     *
     * @return Result code.
     */
    Result initialize();

    /**
     * Set power on.
     *
     * @param device Device to power on.
     * @return Result code.
     */
    Result enable(Device device);

  private:

    /** Mailbox for communicating with the GPU. */
    BroadcomMailbox m_mailbox;

    /** Current bitmask of enabled devices. */
    u32 m_mask;
};

#endif /* __LIBARCH_ARM_BROADCOMPOWER_H */
