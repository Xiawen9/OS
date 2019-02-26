#ifndef __LIBUSB_SYNOPSISCHANNEL_H
#define __LIBUSB_SYNOPSISCHANNEL_H

#include <System.h>
#include <Types.h>
#include <FileSystemMessage.h>
#include "USBMessage.h"

/**
 * Synopsis DesignWare USB Host Controller channels implementation.
 */
class SynopsisChannel
{
  private:

    /** Interrupt number for the Synopsis USB Host Controller. */
    static const uint InterruptNumber = 9;

    /** Number of transfer channels supported by hardware. */
    static const Size ChannelCount = 8;

    /** Size of the channel register block (per channel) */
    static const Size ChannelSize = 0x20;

    /**
     * Controller registers.
     */
    enum Register
    {
        HostChannel       = 0x500,
        HostFrameNumber   = 0x408,
        HostChannelMask   = 0x418
    };

    /**
     * Channel registers.
     *
     * Each of these registers is for a single channel only,
     * starting at the HostChannel register as base offset (channel 0).
     */
    enum ChannelRegister
    {
        Characteristics   = 0x00,
        SplitControl      = 0x04,
        ChannelInterrupt  = 0x08,
        ChannelMask       = 0x0c,
        ChannelTransfer   = 0x10,
        ChannelDMA        = 0x14,
        Reserved1         = 0x18,
        Reserved2         = 0x1c,
        HostChannelSize   = 0x20
    };

    /**
     * Characteristics register flags.
     */
    enum CharacteristicsFlags
    {
        LowSpeed          = (1 << 17),
        ChannelEnable     = (1 << 31)        
    };

    /**
     * ChannelInterrupt register flags.
     */
    enum ChannelInterruptFlags
    {
        TransferCompleted = (1 << 0),
        ChannelHalted     = (1 << 1),
        AHBError          = (1 << 2),
        StallResponse     = (1 << 3),
        NAKResponse       = (1 << 4),
        ACKResponse       = (1 << 5),
        NYETResponse      = (1 << 6),
        TransferError     = (1 << 7),
        BusError          = (1 << 8),
        FrameOverrun      = (1 << 9),
        DataToggleError   = (1 << 10),
        BufferNotReady    = (1 << 11),
        TransferExcess    = (1 << 12),
        FrameListRolover  = (1 << 13)
    };

    /**
     * Packet ID constants.
     */
    enum PacketId
    {
        Data0   = 0,
        Data1   = 2,
        Data2   = 1,
        SetupId = 3
    };

  public:

    /**
     * Channel state.
     */
    enum State
    {
        Idle,
        Active,
        Transfer,
    };

    /**
     * Result codes.
     */
    enum Result
    {
        Success,
        TransferStarted,
        IOError,
        Busy
    };

    /**
     * Constructor
     */
    SynopsisChannel(Size id, Arch::IO *io);

    /**
     * Get channel id.
     *
     * @return Channel id.
     */
    Size getId() const;

    /**
     * Get message.
     *
     * @return FileSystemMessage pointer.
     */
    const FileSystemMessage * getMessage() const;

    /**
     * Get state.
     *
     * @return Channel state
     */
    State getState() const;

    /**
     * Initialize channel.
     *
     * @return Result code.
     */
    Result initialize();

    /**
     * Notify for Channel interrupt.
     *
     * @return Result code.
     */
    Result interrupt();

    /**
     * Start USB transfer.
     */
    Result transfer(const FileSystemMessage *msg,
                    USBMessage *usb);

    /**
     * Equals operator
     */
    bool operator == (const SynopsisChannel & ch) const;

    /**
     * Not-equals operator.
     */
    bool operator != (const SynopsisChannel & ch) const;

  private:

    /** Filesystem message object. */
    const FileSystemMessage *m_msg;

    /** Message object */
    USBMessage *m_usb;

    /** I/O object instance. */
    Arch::IO *m_io;

    /** Register base offset for the current channel (based on its ID number) */
    Size m_base;

    /** Channel identifier. */
    Size m_id;

    /** Channel state. */
    State m_state;
};

#endif /* __LIBUSB_SYNOPSISCHANNEL_H */
