#ifndef __LIBSTD_ARGUMENTCONTAINER_H
#define __LIBSTD_ARGUMENTCONTAINER_H

#include "Types.h"
#include "Macros.h"
#include "String.h"
#include "HashTable.h"
#include "HashIterator.h"
#include "Vector.h"
#include "Argument.h"

/**
 * Generic command-line argument parser.
 */
class ArgumentContainer
{
  private:

  public:

    /**
     * Result codes.
     */
    enum Result
    {
        Success,
        InvalidArgument,
        NotFound
    };

    /**
     * Constructor
     */
    ArgumentContainer();

    /**
     * Destructor
     */
    virtual ~ArgumentContainer();

    /**
     * Get argument by name
     *
     * @param name Name of the argument
     * @return String object pointer if found or ZERO if not found
     */
    const char * get(const char *name) const;

    /**
     * Get positional arguments.
     *
     * @return Vector object reference
     */
    Vector<Argument *> & getPositionals();

    /**
     * Get flag arguments.
     *
     * @return HashTable object reference
     */
    HashTable<String, Argument *> & getFlags();

    /**
     * Add positional argument.
     *
     * @param arg Positional argument
     */
    Result addPositional(Argument *arg);

    /**
     * Add flag argument.
     *
     * @param arg Flag argument
     */
    Result addFlag(Argument *arg);

  private:

    /** Contains all flag arguments. */
    HashTable<String, Argument *> m_flags;

    /** Contains all positional arguments. */
    Vector<Argument *> m_positionals;
};

#endif /* __LIBSTD_ARGUMENTCONTAINER_H */
