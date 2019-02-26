#ifndef __LIBSTD_FACTORY_H
#define __LIBSTD_FACTORY_H

/**
 * Abstract Factory design pattern.
 */
template <class T> class Factory
{
  public:
<<<<<<< HEAD

=======
  
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
    /**
     * Create an instance of T.
     * @return Pointer to T.
     */
    static T * create()
    {
<<<<<<< HEAD
        return new T();
=======
	return new T();
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
    }
};

#endif /* __LIBSTD_FACTORY_H */
