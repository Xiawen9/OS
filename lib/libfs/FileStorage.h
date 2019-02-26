#ifndef __FILESYSTEM_FILESTORAGE_H
#define __FILESYSTEM_FILESTORAGE_H

#include <Types.h>
#include "Storage.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

/**
 * @brief Use a file as Storage provider.
 * @see Storage
 */
class FileStorage : public Storage
{
    public:
    
	/**
	 * @brief Constructor function.
	 * @param path Full path to the file to use.
	 * @param offset Offset in the file as a base for I/O.
	 */
	FileStorage(const char *path, Size offset = ZERO)
	{
	    this->file   = open(path, O_RDWR);
	    this->offset = offset;
	    stat(path, &st);
	}

	/**
	 * @brief Destructor function.
	 */
	~FileStorage()
	{
	    close(file);
	}

	/**
	 * Read a contiguous set of data.
	 * @param offset Offset to start reading from.
	 * @param buffer Output buffer.
	 * @param size Number of bytes to copied.
	 */
	virtual Error read(u64 offset, void *buffer, Size size)
	{
	    int result;
	    
	    if (file >= 0)
	    {
		lseek(file, this->offset + offset, SEEK_SET);
		result = ::read(file, buffer, size);
		
		return result >= 0 ? result : errno;
	    }
	    else
		return errno;
	}
	
	/**
	 * Write a contiguous set of data.
	 * @param offset Offset to start writing to.
	 * @param buffer Input buffer.
	 * @param size Number of bytes to written.
	 */
	Error write(u64 offset, void *buffer, Size size)
	{
	    int result;
	
	    if (file >= 0)
	    {
		lseek(file, this->offset + offset, SEEK_SET);
	        result = ::write(file, buffer, size);
		
		return result >= 0 ? result : errno;
	    }
	    else
		return errno;
	}

	/**
	 * Retrieve maximum storage capacity.
	 * @return Storage capacity.
	 */
	u64 capacity()
	{
	    return st.st_size;
	}
	
    private:
    
	/** @brief File descriptor of the file for Storage I/O. */
	int file;
	
	/** @brief Status of the file for Storage I/O. */
	struct stat st;
	
	/** @brief Offset used as a base for I/O. */
	Size offset;
};

#endif /* __FILESYSTEM_STORAGE_H */
