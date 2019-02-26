#ifndef __LIBSTD_ARRAY_H
#define __LIBSTD_ARRAY_H

#include "Assert.h"
#include "Sequence.h"
#include "Types.h"
#include "Macros.h"

/**
 * This is a wrapper class for a fixed size array.
 * It contains some extra functionality, somewhat like the Arrays class in Java.
 */
template <class T, Size N> class Array : public Sequence<T>
{
  public:

    /**
     * Default constructor
     */
    Array()
    {
    }

    /**
     * Copy constructor.
     *
     * @param a Array reference to copy from.
     */
    Array(const Array<T,N> & a)
    {
        for (Size i = 0; i < N; i++)
        {
            m_array[i] = a->m_array[i];
        }
    }

    /**
     * Puts the given item at the given position.
     * If an item exists at the given position, it will be
     * replaced by the given item.
     *
     * @param position The position to insert the item.
     * @param item The item to put
     * @return bool Whether putting the item at the given position succeeded.
     */
    virtual bool insert(Size position, const T & item)
    {
        if (position >= N)
        {
            return false;
        }
        m_array[position] = item;
        return true;
    }

    /**
     * Returns the item at the given position.
     *
     * @param position The position of the item to get.
     * @return Pointer to the item at the given position.
     */
    virtual const T * get(Size position) const
    {
        if (position >= N)
        {
            return ZERO;
        }
        return &m_array[position];
    }

    /**
     * Returns a reference to the item at the given position.
     * Note that this function does not perform bounds checking.
     * Position must be a valid index.
     *
     * @param position Valid index inside this array.
     * @return Reference to the item at the given position
     */
    virtual const T & at(Size position) const
    {
        return m_array[position];
    }

    /**
     * Return value at the given position.
     * If position is not within bounds of this array,
     * this function will return a default constructed T.
     *
     * @param position Index inside this array.
     * @return T at the given position or default constructed T.
     */
    virtual const T value(Size position) const
    {
        if (position >= N)
            return T();
        else
            return m_array[position];
    }

    /**
     * Returns the maximum size of this Array.
     *
     * @return size The maximum size of this Array.
     */
    virtual Size size() const
    {
        return N;
    }

    /**
     * Returns the number of items in the Array.
     *
     * @return The same as size().
     */
    virtual Size count() const
    {
        return N;
    }

  private:

    /** The actual array where the data is stored. */
    T m_array[N];
};

#endif /* __LIBSTD_ARRAY_H */
