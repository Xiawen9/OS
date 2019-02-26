#ifndef __LIB_LIBFS_PSEUDOFILE_H
#define __LIB_LIBFS_PSEUDOFILE_H

#include <Types.h>
#include "File.h"
#include "IOBuffer.h"

/**
 * @brief Pseudo files only exist in memory.
 */
class PseudoFile : public File
{
  public:

    /**
     * Constructor.
     */
    PseudoFile();

    /**
     * Constructor.
     */
    PseudoFile(const char *str);

    /**
     * Constructor with formatted input.
     *
     * @param format Format string.
     * @param ... Argument list.
     */
    PseudoFile(const char *format, ...);

    /**
     * Destructor.
     */
    virtual ~PseudoFile();

    /** 
     * @brief Read bytes from the file. 
     *
     * @param buffer Output buffer. 
     * @param size Number of bytes to read, at maximum. 
     * @param offset Offset inside the file to start reading. 
     * @return Number of bytes read on success, Error on failure. 
     *
     * @see IOBuffer
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

    /**
     * Write bytes to the file.
     *
     * @param buffer Input/Output buffer to input bytes from.
     * @param size Number of bytes to write, at maximum.
     * @param offset Offset inside the file to start writing.
     * @return Number of bytes written on success, Error on failure.
     */
    virtual Error write(IOBuffer & buffer, Size size, Size offset);

  private:

    /** Buffer from which we read. */
    char *m_buffer;
};

/**
 * @}
 */

#endif /* __LIB_LIBFS_PSEUDOFILE_H */
