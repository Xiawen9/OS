#ifndef __ARM_CONTROL_H
#define __ARM_CONTROL_H

#include<Types.h>
#include<Macros.h>

/**
 * ARM System Control Coprocessor (CP15).
 *
 * The ARM Architecture defines a coprocessor to
 * manage various subsystems in the ARM core, including
 * virtual memory, interrupts, debugging and more.
 * It appears as coprocessor number 15 to the ARM core
 * and is accessible by the MRC (ARM Register from Coprocessor)
 * and MCR () instructions.
 *
 * @see ARM Architecture Reference Manual, page xxx
 */

class ARMControl
{
  public:
    	 /**
    	 * System Control Registers
    	 */	
	enum Register
	{
		MainID = 0,
		SystemControl,
		AuxControl,
		DomainControl,
		TranslationTable0,
		TranslationTable1,
		TranslstionTableCtrl,
		CacheClear,
		DataCacheClean,
		FlushPrefetchBuffer,
		InstructionCacheClear,
		InstructionTLBClear,
		DataTLBClear,
		UnifiedTLBClear,
		UserProcID,
		InstructionFaultAddress,
		InstructionFaultStatus,
		DataFaultAddress,
		DataFaultStatus
	}
	
	/**
      	 * System Control flags.
     	 */
	enum SystemControlFlags
	{
		MMUEnabled  = (1 << 0),
		InstructionCache  = (1 << 12),
		DataCache = (1 << 2),
		ExtendedPaging = (1 << 23),
		AccessPermissions = (1 << 29),
		BranchPrediction = (1 << 11),
		AlignmentCorrect = (1 << 22),
		AlignmentFaults = (1 << 1),
	#ifdef ARMV6
		BigEndian = (1 << 7)
	#else
		BigEngian = (1 << 25)
	#endif
	};
	
	/** 辅助控制标记
   	 * Aux Control flags.
     	 */
	enum AuxControlFlags
	{
		DisablePageColoring = (1 << 6),
		SMPBit = (1 << 6)
	};
	
	 /** 域控制标记
    	  * Domain Control flags.
     	  */
	enum DomainControlFlags
	{
		DomainClient = 1,
		DomainManager = 3
	};

	/**构造函数
     	 * Constructor
    	 */
	ARMControl();

	/**析构函数
         * Destructor
         */
	virtual ~ARMControl();

	/**
         * Read a register from the CP15.
         *
         * @param reg The Register to read.
         * @return 32-bit value of the register.
         */
	u32 read(Register reg);

	/**
         * Write register to the CP15.
         *
         * @param reg The Register to write.
         * @param value 32-value to write.
         */
	void write(Register reg, u32 value);
	
	void set(SystemControlFlags flags);
	void unset(SystemControlFlags flags);
	void set(AuxControlFlags flags);
	void set(DomainControlFlags flags);
	
    private:
	/**
         * Set flag(s) in a CP15 register.
         */
	void set(Register reg, u32 flags);
	
	/**
         * Unset flag(s) in a CP15 register.
         */
	void unset(Register reg, u32 flags);
};

#endif
