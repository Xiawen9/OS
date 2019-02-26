#ifndef __FILESYSTEM_STORAGE_H
#define __FILESYSTEM_STORAGE_H

#include <Types.h>
#include <errno.h>

/**
 * Provides a storage device to build filesystems on top.
 */
class Storage
{
    public:
    
	/**
	 * Constructor function.
	 */
	Storage()
	{
	}

	/**
	 * Destructor function.
	 */
	virtual ~Storage() {}

	/**
	 * Read a contiguous set of data.
	 * @param offset Offset to start reading from.
	 * @param buffer Output buffer.
	 * @param size Number of bytes to copied.
	 */
	virtual Error read(u64 offset, void *buffer, Size size)
	{
	    return ENOTSUP;
	}
	
	/**
	 * Write a contiguous set of data.
	 * @param offset Offset to start writing to.
	 * @param buffer Input buffer.
	 * @param size Number of bytes to written.
	 */
	virtual Error write(u64 offset, void *buffer, Size size)
	{
	    return ENOTSUP;
	}

	/**
	 * Retrieve maximum storage capacity.
	 * @return Storage capacity.
	 */
	virtual u64 capacity() = 0;
};

#endif /* __FILESYSTEM_STORAGE_H */
