#ifndef __SINGLETON_H
#define __SINGLETON_H

template <class T> class Singleton
{
  public:
    Singleton<T>(T *obj)
    {
        instance = obj;
    }
    static T *instance;
};

template <class T> T* Singleton<T>::instance = 0;

#endif /* __SINGLETON_H */
