#ifndef __PCI_PCIREGISTER_H
#define __PCI_PCIREGISTER_H

#include <Types.h>
#include "File.h"
#include "FileMode.h"
#include "Directory.h"
#include "IOBuffer.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/**
 * @brief Represent a PCI configuration register as a File.
 *
 * This class reads out a register directly from the PCI
 * configuration space.
 *
 * @see PCIServer
 * @see File
 */
class PCIRegister : public File
{
    public:

	/**
	 * @brief Constructor function.
	 * @param bus PCI bus number.
	 * @param slot PCI slot on the bus.
	 * @param func PCI device function number.
	 * @param reg PCI configuration register to access.
	 * @param size The size of the register.
	 */
	PCIRegister(u16 bus, u16 slot, u16 func, u16 reg, Size size);

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
    
	/** @brief PCI register for I/O. */
	u16 reg;
	
	/** @brief Size of the register in bytes. */
	Size size;
};

/**
 * @}
 */

#endif /* __PCI_PCIREGISTER_H */
