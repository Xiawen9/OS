#ifndef __LIBSTD_CONTAINER_H
#define __LIBSTD_CONTAINER_H

#include "Types.h"
#include "Macros.h"

/**
 * Containers provide access to stored items.
 */
class Container
{
  public:
<<<<<<< HEAD

=======
    
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
    /**
     * Constructor.
     */
    Container();

    /**
     * Destructor.
     */
    virtual ~Container();

    /**
     * Returns the maximum size of this Container.
     *
     * @return size The maximum size of this Container.
     */
    virtual Size size() const = 0;

    /**
     * Returns the number of items inside the Container.
<<<<<<< HEAD
=======
     * 
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
     * @return Number of items inside the Container.
     */
    virtual Size count() const = 0;

    /**
     * Removes all items from the Container.
     */
    virtual void clear() = 0;

    /**
<<<<<<< HEAD
     * Check if the Container is empty.
     *
     * @return True if empty, false otherwise.
     */
    virtual bool isEmpty() const;

=======
     * check if the Container is empty.
     * 
     * @return True if empty, false otherwise.
     */
    virtual bool isEmpty() const;
  
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
    /**
     * Ensure that at least the given size is available.
     *
     * @param size Size to reserve in the Container
     * @return True if the given size is reserved, false otherwise.
     */
    virtual bool reserve(Size size);

    /**
     * Shrink the container size by the given amount of items.
     *
     * @param size Number of items to shrink.
     * @return True if shrink succeeded, false otherwise.
     */
    virtual bool shrink(Size size);

    /**
     * Try to minimize the memory required in the Container.
     *
     * @return New size of the Container.
     */
    virtual Size squeeze();

    /**
     * Change the size of the Container.
     *
<<<<<<< HEAD
     * @param size New size of the container.
=======
     * @param size New size of the Container.
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
     * @return True if the resize succeeded, false otherwise.
     */
    virtual bool resize(Size size);
};

#endif /* __LIBSTD_CONTAINER_H */
<<<<<<< HEAD
=======
}
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
