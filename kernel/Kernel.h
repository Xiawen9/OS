#ifndef __KERNEL_H
#define __KERNEL_H

#include <Macros.h>
#include <Types.h>
#include <Singleton.h>
#include <BootImage.h>
#include <Memory.h>
#include <CoreInfo.h>
#include "Process.h"
#include "ProcessManager.h"

class API;
class SplitAllocator;
class IntController;
class Timer;
struct CPUState;

typedef void InterruptHandler(struct CPUState *state, ulong param);

typedef struct InterruptHook
{
    InterruptHook(InterruptHandler *h, ulong p) : handler(h), param(p)
    {
    }

    bool operator == (InterruptHook *i)
    {
        return handler == i->handler && param == i->param;
    }

    InterruptHandler *handler;

    ulong param;
}
InterruptHook;

class Kernel : public Singleton<Kernel>
{
  public:

    enum Result
    {
        Success,
        InvalidBootImage,
        ProcessError
    };

    Kernel(CoreInfo *info);

    static Error heap(Address base, Size size);

    SplitAllocator * getAllocator();

    ProcessManager * getProcessManager();

    API * getAPI();

    MemoryContext * getMemoryContext();

    CoreInfo * getCoreInfo();

    Timer * getTimer();

    int run();

    void enableIRQ(u32 irq, bool enabled);

    virtual void hookIntVector(u32 vec, InterruptHandler h, ulong p);

    virtual void executeIntVector(u32 vec, CPUState *state);

    virtual Result loadBootImage();

  private:

    virtual Result loadBootProcess(BootImage *image, Address imagePAddr, Size index);

  protected:

    SplitAllocator *m_alloc;
    ProcessManager *m_procs;
    API *m_api;
    CoreInfo *m_coreInfo;
    Vector<List<InterruptHook *> *> m_interrupts;
    IntController *m_intControl;
    Timer *m_timer;
};

#endif /* __KERNEL_H */
