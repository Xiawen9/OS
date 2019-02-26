#include <System.h>
#include <Log.h>
#include <SplitAllocator.h>
#include <CoreInfo.h>
#include <arm/ARMInterrupt.h>
#include <arm/ARMConstant.h>
#include <arm/broadcom/BroadcomInterrupt.h>
#include "ARMKernel.h"

ARMKernel::ARMKernel(ARMInterrupt *intr,
                     CoreInfo *info)
    : Kernel(info)
{
    NOTICE("");

    // Setup interrupt callbacks
    m_intControl = intr;
    intr->install(ARMInterrupt::UndefinedInstruction, undefinedInstruction);
    intr->install(ARMInterrupt::SoftwareInterrupt, trap);
    intr->install(ARMInterrupt::PrefetchAbort, prefetchAbort);
    intr->install(ARMInterrupt::DataAbort, dataAbort);
    intr->install(ARMInterrupt::Reserved, reserved);
    intr->install(ARMInterrupt::IRQ, interrupt);
    intr->install(ARMInterrupt::FIQ, interrupt);

    // Enable clocks and irqs
    m_timer = &m_bcmTimer;
    m_bcmTimer.setFrequency( 250 ); /* trigger timer interrupts at 250Hz (clock runs at 1Mhz) */
    m_intControl->enable(BCM_IRQ_SYSTIMERM1);

    // Set ARMCore modes
    ARMControl ctrl;
    ctrl.set(ARMControl::AlignmentFaults);

#ifdef ARMV6
    ctrl.unset(ARMControl::AlignmentCorrect);
    ctrl.unset(ARMControl::BigEndian);
#endif
}

void ARMKernel::interrupt(CPUState state)
{
    ARMKernel *kernel = (ARMKernel *) Kernel::instance;
    ARMInterrupt *intr = (ARMInterrupt *) kernel->m_intControl;

    // TODO: remove BCM2835 specific code
    if (intr->isTriggered(BCM_IRQ_SYSTIMERM1))
    {
        kernel->m_timer->tick();
        kernel->getProcessManager()->schedule();
    }
    for (uint i = BCM_IRQ_SYSTIMERM1+1; i < 64; i++)
    {
        if (intr->isTriggered(i))
        {
            kernel->executeIntVector(i, &state);
        }
    }
}

void ARMKernel::undefinedInstruction(CPUState state)
{
    ARMCore core;
    core.logException(&state);
    FATAL("procId = " << Kernel::instance->getProcessManager()->current()->getID());
    for(;;);
}

void ARMKernel::prefetchAbort(CPUState state)
{
    ARMCore core;
    core.logException(&state);
    FATAL("procId = " << Kernel::instance->getProcessManager()->current()->getID());
    for(;;);
}

void ARMKernel::dataAbort(CPUState state)
{
    ARMCore core;
    core.logException(&state);
    FATAL("procId = " << Kernel::instance->getProcessManager()->current()->getID());
    for(;;);
}


void ARMKernel::reserved(CPUState state)
{
    ARMCore core;
    core.logException(&state);
    FATAL("procId = " << Kernel::instance->getProcessManager()->current()->getID());
    for(;;);
}

void ARMKernel::trap(CPUState state)
{
    //DEBUG("procId = " << Kernel::instance->getProcessManager()->current()->getID() << " api = " << state.r0);

    state.r0 = Kernel::instance->getAPI()->invoke(
        (API::Number) state.r0,
                      state.r1,
                      state.r2,
                      state.r3,
                      state.r4,
                      state.r5
    );
}
