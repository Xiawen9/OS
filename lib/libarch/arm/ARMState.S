#include "ARMConstant.h"

.global switchCoreState
.section ".text"

switchCoreState:

    /* Setup correct stackframe. */

    /* currentStack == 0? */
    cmp r0, #0
    beq restoreState

    /* Save kernel registers on current stack. */
    push {r0-r12}
    push {lr}

    /* Save stack pointer in currentStack */
    stm r0, {sp}

restoreState:

    /* Reload stack */
    mov sp, r1
    mov r4, #0

    /* Restore kernel registers. */
    pop {lr}
    pop {r0-r12}
    mov pc, lr
