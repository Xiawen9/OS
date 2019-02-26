#ifndef __FILESYSTEM_BOOTIMAGESTORAGE_H
#define __FILESYSTEM_BOOTIMAGESTORAGE_H

#include <System.h>
#include <Types.h>
#include <BootImage.h>
#include "Storage.h"
#include <string.h>

/**
 * Uses a BootImage symbol entry as filesystem storage provider (aka RamFS).
 */
class BootImageStorage : public Storage
{
    public:
    
    /**
     * Constructor function.
     *
     * @param name Name of the BootSymbol entry to use.
     */
    BootImageStorage(const char *name)
    {
        m_name   = name;
        m_data   = ZERO;
        m_size   = 0;
    }

    /**
     * Loads the boot module into virtual memory.
     * @return True on success, false otherwise.
     */
    bool load()
    {
        SystemInformation info;
        BootImage *image;
        BootSymbol *symbol;
        BootSegment *segment;
        Memory::Range range;
        u8 *base;

        // Request boot image memory
        range.size   = info.bootImageSize;
        range.access = Memory::User |
                       Memory::Readable;
        range.virt   = ZERO;
        range.phys   = info.bootImageAddress;
        VMCtl(SELF, Map, &range);

        // Update our state
        image = (BootImage *) range.virt;
        base  = (u8 *) image;

        // Search for the given BootSymbol
        for (uint i = 0; i < image->symbolTableCount; i++)
        {
            symbol = (BootSymbol *) (base + image->symbolTableOffset);
            symbol += i;

            if (strcmp(symbol->name, m_name) == 0)
            {
                m_size   = symbol->segmentsTotalSize;

                segment = (BootSegment *) (base + image->segmentsTableOffset +
                                          (symbol->segmentsOffset * sizeof(BootSegment)));
                m_data   = base + segment->offset;
                // Success
                return true;
            }
        }
        // BootSymbol not found
        return false;
    }

    /**
     * Reads data from the boot module.
     * @param offset Offset to start reading from.
     * @param buffer Output buffer.
     * @param size Number of bytes to copied.
     */
    Error read(u64 offset, void *buffer, Size size)
    {
        memcpy(buffer, m_data + offset, size);
        return size;
    }

    /**
     * Retrieve maximum storage capacity.
     * @return Storage capacity.
     */
    u64 capacity()
    {
        return m_size;
    }

  private:
    
    /** Name of the BootSymbol */
    const char *m_name;

    /** Data pointer */
    u8 *m_data;
    
    /** Size of the BootSymbol. */
    Size m_size;
};

#endif /* __FILESYSTEM_BOOTIMAGESTORAGE_H */