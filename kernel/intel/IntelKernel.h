#ifndef __INTEL_KERNEL_H
#define __INTEL_KERNEL_H

#include <Types.h>
#include <BootImage.h>

inline ulong trapKernel1(ulong num, ulong arg1)
{
    ulong ret;
    asm volatile ("int $0x90" : "=a"(ret) : "a"(num), "c"(arg1) : "memory");
    return ret;
}

inline ulong trapKernel2(ulong num, ulong arg1, ulong arg2)
{
    ulong ret;
    asm volatile ("int $0x90" : "=a"(ret) : "a"(num), "c"(arg1), "b"(arg2) : "memory");
    return ret;
}

inline ulong trapKernel3(ulong num, ulong arg1, ulong arg2, ulong arg3)
{
    ulong ret;
    asm volatile ("int $0x90" : "=a"(ret) : "a"(num), "c"(arg1), "b"(arg2),
                        "d"(arg3) : "memory");
    return ret;
}

inline ulong trapKernel4(ulong num, ulong arg1, ulong arg2, ulong arg3,
             ulong arg4)
{
    ulong ret;
    asm volatile ("int $0x90" : "=a"(ret) : "a"(num), "c"(arg1), "b"(arg2),
                        "d"(arg3), "S"(arg4) : "memory");
    return ret;
}

inline ulong trapKernel5(ulong num, ulong arg1, ulong arg2, ulong arg3,
             ulong arg4, ulong arg5)
{
    ulong ret;
    asm volatile ("int $0x90" : "=a"(ret) : "a"(num), "c"(arg1), "b"(arg2),
                 "d"(arg3), "S"(arg4), "D"(arg5) : "memory");
    return ret;
}

#include <Kernel.h>
#include <intel/IntelPIT.h>
#include <intel/IntelPIC.h>
#include <intel/IntelAPIC.h>
#include <Timer.h>

#define IRQ(vector) \
    (vector) + 32

class IntelKernel : public Kernel
{
  public:

    IntelKernel(CoreInfo *info);

  private:

    static void exception(CPUState *state, ulong param);
        
    static void interrupt(CPUState *state, ulong param);

    static void trap(CPUState *state, ulong param);
    
    static void clocktick(CPUState *state, ulong param);

    IntelPIT m_pit;

    IntelAPIC m_apic;

    IntelPIC m_pic;
};
#endif /* __INTEL_KERNEL_H */
