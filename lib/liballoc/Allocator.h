#ifndef __LIBALLOC_ALLOCATOR_H
#define __LIBALLOC_ALLOCATOR_H
#ifndef __ASSEMBLER__

#include <Macros.h>
#include <Types.h>

class Allocator
{
  public:
    enum Result
    {
        Success = 0,
        InvalidAddress,
        InvalidSize,
        InvalidAlignment,
        OutOfMemory
    };
    Allocator();
    virtual ~Allocator();
    static void setDefault(Allocator *alloc);
    static Allocator *getDefault();
    void setParent(Allocator *parent);
    Result setAlignment(Size size);
    Result setBase(Address addr);
    virtual Size size() = 0;
    virtual Size available() = 0;
    virtual Result allocate(Size *size, Address *addr, Size align = ZERO) = 0;
    virtual Result release(Address addr) = 0;

  protected:
    Address aligned(Address addr, Size boundary);
    Allocator *m_parent;
    Size m_alignment;
    Address m_base;
    
  private:
    static Allocator *m_default; 
};

#ifndef __HOST__

inline void * operator new(__SIZE_TYPE__ sz)
{
    Address addr;

    if (Allocator::getDefault()->allocate((Size *) &sz, &addr) == Allocator::Success)
        return (void *) addr;
    else
        return (void *) NULL;
}

inline void * operator new[](__SIZE_TYPE__ sz)
{
    Address addr;

    if (Allocator::getDefault()->allocate((Size *) &sz, &addr) == Allocator::Success)
        return (void *) addr;
    else
        return (void *) NULL;
}

inline void operator delete (void *mem)
{
    Allocator::getDefault()->release((Address)mem);
}

inline void operator delete[] (void *mem)
{
    Allocator::getDefault()->release((Address)mem);
}


inline void * operator new(__SIZE_TYPE__ sz, Address addr)
{
    return (void *) addr;
}

#endif /* __HOST__ */

#endif /* __ASSEMBLER__ */
#endif /* __LIBALLOC_ALLOCATOR_H */
