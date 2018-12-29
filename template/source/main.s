.section .init
.globl _start
_start:

ldr r0,=0x20200000
mov r1, #1
lsl r1, #21
str r1, [r0, #0x10] // set GPIO function select

// set 15 bit of r1
mov r1, #1
lsl r1, #15

loop$:
// turn on LED ACT, GPIO 47, by clearing the GPEDS1 (event detect status reg)
str r1, [r0, #0x2C]

// delay
mov r2, #0x7e0000
wait1$:
	sub r2, #1
	cmp r2, #0
	bne wait1$

// turn off LED
str r1, [r0, #0x20]

// delay
mov r2, #0x7e0000
wait2$:
	sub r2, #1
	cmp r2, #0
	bne wait2$

b loop$
