// Assembly code for interrupt vector table and safely setting up
// execution in interrupt context on the Rapsberry Pi in CS107E. 
//
// Author:      Philip Levis
// Date:        6/20/17

/*
 * Enable/disable interrupts.
 *
 * CPSR = current program status register
 *        upper bits are differen carry flags.
 *        lower 8:
 *          7 6 5 4 3 2 1 0
 *          +-+-+-+---------+
 *          |I|F|T|   Mode  |
 *          +-+-+-+---------+
 *
 *  I : disables IRQ when = 1.
 *  F : disables FIQ when = 1.
 *  T : = 0 indicates ARM execution, = 1 is thumb execution.
 *      Mode = current mode.
 */

.global interrupts_global_enable
interrupts_global_enable:
    mrs r0,cpsr
    bic r0,r0,#0x80 // I=0 enables interrupts
    msr cpsr_c,r0
    bx lr

.global interrupts_global_disable
interrupts_global_disable:
    mrs r0,cpsr
    orr r0,r0,#0x80 // I=1 disables interrupts
    msr cpsr_c,r0
    bx lr

        
.global _vectors
.global _vectors_end
.global _interrupt_asm
        
_vectors:
    ldr pc, _reset_asm
    ldr pc, _undefined_instruction_asm
    ldr pc, _software_interrupt_asm
    ldr pc, _prefetch_abort_asm
    ldr pc, _data_abort_asm
    ldr pc, _reset_asm
    ldr pc, _interrupt_asm
    
fast_interrupt_asm:
    sub   lr, lr, #4            @ First instr of FIQ handler
    push  {lr}
    push  {r0-r12}
    mov   r0, lr                @ Pass old pc
    bl    fast_interrupt_vector @ C function
    pop   {r0-r12}
    ldm   sp!, {pc}^

_reset_asm:                   .word reset_asm
_undefined_instruction_asm:   .word undefined_instruction_asm
_software_interrupt_asm:      .word software_interrupt_asm
_prefetch_abort_asm:          .word prefetch_abort_asm
_data_abort_asm:              .word data_abort_asm
_interrupt_asm:               .word interrupt_asm

_vectors_end:

interrupt_asm:
    sub   lr, lr, #4
    push  {lr}
    push  {r0-r12}
    mov   r0, lr              @ Pass old pc
    bl    interrupt_vector    @ C function
    pop   {r0-r12}
    ldm   sp!, {pc}^

reset_asm:
    sub   lr, lr, #4
    push  {lr}
    push  {r0-r12}
    mov   r0, lr              @ Pass old pc
    bl    reset_vector        @ C function
    pop   {r0-r12}
    ldm   sp!, {pc}^

undefined_instruction_asm:
    sub   lr, lr, #4
    push  {lr}
    push  {r0-r12}
    mov   r0, lr                          @ Pass old pc
    bl    undefined_instruction_vector    @ C function
    pop   {r0-r12}
    ldm   sp!, {pc}^

software_interrupt_asm:
    sub   lr, lr, #4
    push  {lr}
    push  {r0-r12}
    mov   r0, lr                       @ Pass old pc
    bl    software_interrupt_vector    @ C function
    pop   {r0-r12}
    ldm   sp!, {pc}^

prefetch_abort_asm:
    sub   lr, lr, #4
    push  {lr}
    push  {r0-r12}
    mov   r0, lr                   @ Pass old pc
    bl    prefetch_abort_vector    @ C function
    pop   {r0-r12}
    ldm   sp!, {pc}^

data_abort_asm:
    sub   lr, lr, #4
    push  {lr}
    push  {r0-r12}
    mov   r0, lr                 @ Pass old pc
    bl    data_abort_vector      @ C function
    pop   {r0-r12}
    ldm   sp!, {pc}^
