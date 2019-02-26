#ifndef __LIBARCH_COREMANAGER_H
#define __LIBARCH_COREMANAGER_H

#include <Types.h>
#include <List.h>
#include "CoreInfo.h"

/**
 * Generic Core Manager.
 */
class CoreManager
{
  private:

  public:

    /**
     * Result codes.
     */
    enum Result
    {
        Success,
        IOError,
        NotFound
    };

    /**
     * Constructor
     */
    CoreManager();

    /**
     * Get list of core identities.
     *
     * @return List of core identities.
     */
    List<uint> & getCores();

    /**
     * Discover processors.
     *
     * @return Result code.
     */
    virtual Result discover() = 0;

    /**
     * Boot a processor.
     *
     * @param info CoreInfo object pointer.
     * @return Result code.
     */
    virtual Result boot(CoreInfo *info) = 0;

  protected:

    /** List of core ids found. */
    List<uint> m_cores;
};

#endif /* __LIBARCH_COREMANAGER_H */
