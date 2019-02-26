#ifndef __LIBSTD_BITARRAY_H
#define __LIBSTD_BITARRAY_H

#include "Macros.h"
#include "Assert.h"
#include "Types.h"

#define BITS_TO_BYTES(bits) ((bits / 8) + ((bits % 8) ? 1 : 0))

class BitArray
{
  public:
    enum Result
    {
        Success,
        InvalidArgument,
        OutOfMemory
    };

    BitArray(Size size, u8 *array = ZERO);
    ~BitArray();

    /**
     * Returns the maximum size of this Container.
     *
     * @return size The maximum size of this Container.
     */
    Size size() const;

    /**
     * Get the number of bits in the map which have the given value.
     *
     * @param on True to get the number of 1-bits, false for 0-bits.
     * @return Number of bits with the given value.
     */
    Size count(bool on) const;

    /**
     * Sets the given bit to the given value.
     *
     * @param bit Bit number to set.
     * @param value Value to set.
     */
    void set(Size bit, bool value = true);

    /**
     * Set a range of bits inside the map to 1.
     * @param from Bit to start with.
     * @param to End bit (inclusive).
     */
    void setRange(Size from, Size to);

    /**
     * Sets the next unset bit(s).
     *
     * @param bit Start bit number on success.
     * @param count Number of consequetive bits required.
     * @param offset Start bit number to start searching at inside the BitArray.
     * @param boundary First bit number must be on the given alignment boundary.
     * @return Result code.
     */
    Result setNext(Size *bit, Size count = 1, Size offset = 0, Size boundary = 1);

    /**
     * Sets the given bit to zero.
     *
     * @param bit Bit number to unset.
     */
    void unset(Size bit);
    void clear();

    /**
     * Verify if a given bit is set.
     * @param bit Bit number to check.
     * @return True if marked, false otherwise.
     */
    bool isSet(Size bit) const;

    /**
     * Retrieve a pointer to the internal BitArray.
     * @return Internal BitArray.
     */
    u8 * array() const;

    /**
     * Use the given pointer as the BitArray buffer.
     * @param array New bits array pointer.
     * @param size New number of bits. ZERO to keep the old value.
     */
    void setArray(u8 *array, Size size = ZERO);

    /**
     * Retrieve the value of the given bit.
     */
    bool operator[](Size bit) const;

    /**
     * Retrieve the value of the given bit.
     */
    bool operator[](int bit) const;

  private:

    /** Total number of bits in the array. */
    Size m_size;

    /** Set bits in the array. */
    Size m_set;

    /** Array containing the bits. */
    u8 *m_array;

    /** True if m_array was allocated interally. */
    bool m_allocated;
};

#endif /* __LIBSTD_BITARRAY_H */
