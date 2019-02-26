#ifndef __ARM_RASPBERRY_SYSTEM_H
#define __ARM_RASPBERRY_SYSTEM_H

/*Raspberry Pi A/B/B+ have a Broadcom 2835 SoC */
#define __SYSTEM
#define ARM
#define ARMV6
#define BCM2835

/** Default IO base on the Broadcom 2835 */
#define IO_BASE 0x20000000
#define IO_SIZE (1024*1024*128)

#include <arm/ARMConstant.h>
#include <arm/ARMCore.h>
#include <arm/ARMCacheV6.h>
#include <arm/ARMIO.h>
#include <arm/ARMState.h>
#include <arm/ARMPaging.h>
#include <arm/ARMMap.h>
#include <arm/ARMKernel.h>
#include <arm/ARMProcess.h>

#include <API.h>

#endif
