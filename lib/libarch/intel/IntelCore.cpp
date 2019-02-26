#include <Log.h>
#include <String.h>
#include "IntelCore.h"

void IntelCore::logException(CPUState *state)
{
    String s;

    switch (state->vector)
    {
        case INTEL_DIVZERO:
            ERROR("Divide Error Exception");
            break;

        case INTEL_DEBUGEX:
            ERROR("Debug Exception");
            break;

        case INTEL_NMI:
            ERROR("Non-Maskable Interrupt Exception");
            break;

        case INTEL_BREAKP:
            ERROR("Breakpoint Exception");
            break;

        case INTEL_OVERFLOW:
            ERROR("Overflow Exception");
            break;

        case INTEL_BOUNDS:
            ERROR("BOUND Range Exceeded Exception");
            break;

        case INTEL_OPCODE:
            ERROR("Invalid Opcode Exception");
            break;

        case INTEL_DEVERR:
            ERROR("Device Not Available Exception");
            break;

        case INTEL_DOUBLEF:
            ERROR("Double Fault Exception");
            break;

        case INTEL_COSEG:
            ERROR("Coprocessor Segment Overrun Exception");
            break;

        case INTEL_TSSERR:
            ERROR("Invalid Task State Segment Exception");
            break;

        case INTEL_SEGERR:
            ERROR("Segment Not Present Exception");
            break;

        case INTEL_STACKERR:
            ERROR("Stack Fault Exception");
            break;

        case INTEL_GENERR:
            ERROR("General Protection Fault Exception");
            break;

        case INTEL_PAGEFAULT:
            ERROR("Page Fault Exception");
            // TODO: modify Log() to accept a String.
            s << "Error " << state->error << " at " << Number::Hex << readCR2();
            ERROR(*s);
            break;

        case INTEL_FLOATERR:
            ERROR("Floating Point Error Exception");
            break;

        case INTEL_ALIGNERR:
            ERROR("Alignment Check Exception");
            break;

        case INTEL_MACHCHK:
            ERROR("Machine Check Exception");
            break;

        case INTEL_SIMD:
            ERROR("SIMD Floating Point Exception");
            break;

        case INTEL_VIRTERR:
            ERROR("Virtualization Exception");
            break;

        default:
            ERROR("Unknown Exception: " << state->vector);
            break;
    }
    logState(state);
}

void IntelCore::logState(CPUState *state)
{
    logRegister("eip", state->irq.eip);
    logRegister("eax", state->regs.eax);
    logRegister("ebx", state->regs.ebx);
    logRegister("ecx", state->regs.ecx);
    logRegister("edx", state->regs.edx);
    logRegister("esi", state->regs.esi);
    logRegister("edi", state->regs.edi);
    logRegister("ebp", state->regs.ebp);
    logRegister("esp", state->regs.esp0);
}

void IntelCore::logRegister(const char *name, u32 reg)
{
    String s;
    s << Number::Hex << name << " = " << reg << Number::Dec << " (" << reg << ")";

    ERROR(*s);
}

u32 IntelCore::readCR2()
{
    u32 cr2;
    asm volatile("mov %%cr2, %%eax\n"
                 "mov %%eax, %0\n" : "=r" (cr2));
    return cr2;
}

u32 IntelCore::readCR3()
{
    u32 cr3;
    asm volatile("mov %%cr3, %%eax\n"
                 "mov %%eax, %0\n" : "=r" (cr3));
    return cr3;
}

void IntelCore::writeCR3(u32 cr3)
{
    asm volatile("mov %0, %%eax\n"
                 "mov %%eax, %%cr3" :: "r" (cr3));
}
