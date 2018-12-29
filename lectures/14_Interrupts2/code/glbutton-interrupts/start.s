// The reference full assembly start sequence for CS107E.
// This sets up the stack and other execution context for
// interrupt mode, fast interrupt mode, and supervisor mode
// before branching to _cstart (in cstart.c). It sets up the
// frame pointer in fast interrupt mode in case someone wants
// to backtrace in that mode.
//
// If _cstart() returns, _start hangs in an infinite loop.
//
// Author: Philip Levis
// Date: 6/20/2017
.globl _start
_start:
    mov r0, #0xD2  // Interrupts
    msr cpsr_c, r0
    mov sp, #0x8000
    mov r0, #0xD1  // Fast interrupts
    msr cpsr_c, r0       
    mov sp, #0x4000       
    mov fp, #0     // FIQ has fp
    mov r0, #0xD3  // Supervisor
    msr cpsr_c, r0      
    mov sp, #0x8000000
    mov fp, #0
    bl _cstart

hang: b hang

