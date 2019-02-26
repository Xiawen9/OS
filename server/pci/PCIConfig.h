#ifndef __PCI_PCICONFIG_H
#define __PCI_PCICONFIG_H

#include <Types.h>
#include "File.h"
#include "FileMode.h"
#include "Directory.h"
#include "IOBuffer.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/**
 * @brief Represent the raw PCI configuration as a File.
 *
 * This class reads and writes directly from and to the PCI
 * configuration space, for a given PCI device on the bus.
 *
 * @see PCIServer
 * @see File
 */
class PCIConfig : public File
{
    public:

	/**
	 * @brief Constructor function.
	 * @param bus PCI bus number.
	 * @param slot PCI slot on the bus.
	 * @param func PCI device function number.
	 */
	PCIConfig(u16 bus, u16 slot, u16 func);

	/** 
         * @brief Read bytes from the file. 
	 *
         * @param buffer Output buffer. 
         * @param size Number of bytes to read, at maximum. 
         * @param offset Offset inside the file to start reading. 
         * @return Number of bytes read on success, Error on failure. 
	 *
	 * @see IOBuffer
	 * @see PCIServer.h
         */
        Error read(IOBuffer *buffer, Size size, Size offset);
	
    private:

	/** @brief PCI bus number. */
	u16 bus;
	
	/** @brief PCI slot number. */
	u16 slot;
	
	/** @brief PCI device function number. */
	u16 func;
};

/**
 * @}
 */

#endif /* __PCI_PCICONFIG_H */
