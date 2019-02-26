#ifndef __LIBSTD_FACTORY_H
#define __LIBSTD_FACTORY_H

/**
 * Abstract Factory design pattern.
 */
template <class T> class Factory
{
  public:

    /**
     * Create an instance of T.
     * @return Pointer to T.
     */
    static T * create()
    {
        return new T();
    }
};

#endif /* __LIBSTD_FACTORY_H */
