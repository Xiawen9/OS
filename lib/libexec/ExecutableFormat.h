#ifndef __LIBEXEC_EXECUTABLEFORMAT_H
#define __LIBEXEC_EXECUTABLEFORMAT_H
#ifndef __ASSEMBLER__

#include <Memory.h>
#include <Types.h>

/**  
 * @defgroup libexec libexec
 * @{  
 */

/** Entry point of a program. */
typedef Address EntryPoint;

/** Forward declaration. */
class ExecutableFormat;

/**
 * Confirms if we understand the given format.
 * @return true on success and false on failure.
 */
typedef ExecutableFormat * FormatDetector(u8 *image, Size size);

/**
 * Abstraction class of various executable formats.
 */
class ExecutableFormat
{
  public:

    /**
     * Memory region.
     */
    typedef struct Region
    {
        Address virt;
        Size size;
        Memory::Access access;
        u8 *data;
    }
    Region;

    /**
     * Result code
     */
    enum Result
    {
        Success,
        NotFound,
        InvalidFormat,
        OutOfMemory
    };

    /**
     * Class constructor.
     *
     * @param image Pointer to program image.
     * @param size Size of the program image.
     */
    ExecutableFormat(u8 *image, Size size);

    /**
     * Class destructor.
     */
    virtual ~ExecutableFormat();

    /**
     * Memory regions a program needs at runtime.
     *
     * @param regions Memory regions to fill.
     * @param count On input, the maximum number of regions to read.
     *              On output, the actual number of regions read.
     * @return Result code.
     */
    virtual Result regions(Region *regions, Size *count) = 0;

    /**
     * Lookup the program entry point.
     *
     * @param entry Entry point on output.
     * @return Result code.
     */
    virtual Result entry(Address *entry) = 0;

    /**
     * Find a ExecutableFormat which can handle the given format.
     *
     * @param image Program image to read.
     * @param size Program image size.
     * @param fmt ExecutableFormat object pointer on output.
     * @return Result code.
     */
    static Result find(u8 *image, Size size, ExecutableFormat **fmt);

  protected:

    u8 *m_image;

    Size m_size;
};

/**
 * @}
 */

#endif /* __ASSEMBLER__ */
#endif /* __LIBEXEC_EXECUTABLEFORMAT_H */
