#include "ARMCore.h"
#include "ARMControl.h"

ARMControl::ARMControl()
{
}

ARMControl::~ARMControl()
{
}

u32 ARMControl::read(Register reg)
{
    switch (reg)
    {
        case MainID:               return mrc(p15, 0, 0, c0,  c0);
        case SystemControl:        return mrc(p15, 0, 0, c1,  c0);
        case AuxControl:           return mrc(p15, 0, 1, c1,  c0);
        case TranslationTable0:    return mrc(p15, 0, 0, c2,  c0);
        case TranslationTable1:    return mrc(p15, 0, 1, c2,  c0);
        case TranslationTableCtrl: return mrc(p15, 0, 2, c2,  c0);
        case DomainControl:        return mrc(p15, 0, 0, c3,  c0);
        case UserProcID:           return mrc(p15, 0, 4, c13, c0);
        case InstructionFaultAddress: return mrc(p15, 0, 2, c6, c0);
        case InstructionFaultStatus:  return mrc(p15, 0, 1, c5, c0);
        case DataFaultAddress:        return mrc(p15, 0, 0, c6, c0);
        case DataFaultStatus:         return mrc(p15, 0, 0, c5, c0);
        default: break;
    }
    return 0;
}

void ARMControl::write(Register reg, u32 value)
{
    switch (reg)
    {
        case SystemControl:         mcr(p15, 0, 0, c1,  c0, value); break;
        case AuxControl:            mcr(p15, 0, 1, c1,  c0, value); break;
        case TranslationTable0:     mcr(p15, 0, 0, c2,  c0, value); break;
        case TranslationTable1:     mcr(p15, 0, 1, c2,  c0, value); break;
        case TranslationTableCtrl:  mcr(p15, 0, 2, c2,  c0, value); break;
        case DomainControl:         mcr(p15, 0, 0, c3,  c0, value); break;
        case CacheClear:            mcr(p15, 0, 0, c7,  c7, value); break;
        case DataCacheClean:        mcr(p15, 0, 0, c7, c14, value); break;
        case FlushPrefetchBuffer:   mcr(p15, 0, 4, c7,  c5, value); break;
        case InstructionCacheClear: mcr(p15, 0, 0, c7,  c5, value); break;
        case InstructionTLBClear:   mcr(p15, 0, 0, c8,  c5, value); break;
        case DataTLBClear:          mcr(p15, 0, 0, c8,  c6, value); break;
        case UnifiedTLBClear:       mcr(p15, 0, 0, c8,  c7, value); break;
        case UserProcID:            mcr(p15, 0, 4, c13, c0, value); break;
        default: break;
    }
}

void ARMControl::set(Register reg, u32 flags)
{
    u32 val = read(reg);
    val |= flags;
    write(reg, val);
}

void ARMControl::unset(Register reg, u32 flags)
{
    u32 val = read(reg);
    val &= ~(flags);
    write(reg, val);
}

void ARMControl::set(ARMControl::SystemControlFlags flags)
{
    set(SystemControl, flags);
}

void ARMControl::unset(ARMControl::SystemControlFlags flags)
{
    unset(SystemControl, flags);
}

void ARMControl::set(ARMControl::AuxControlFlags flags)
{
    set(AuxControl, flags);
}

void ARMControl::set(ARMControl::DomainControlFlags flags)
{
    set(DomainControl, flags);
}
