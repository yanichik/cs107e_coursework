	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 1
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"cstart.c"
	.text
	.align	2
	.global	_cstart
	.type	_cstart, %function
_cstart:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r3, lr}
	ldr	r3, .L4
	ldr	r2, .L4+4
	mov	r1, #0
	b	.L2
.L3:
	str	r1, [r3]
	add	r3, r3, #4
.L2:
	cmp	r3, r2
	bcc	.L3
	bl	main
	ldr	r3, .L4+8
	mov	r2, #2097152
	str	r2, [r3, #16]
	mov	r2, #32768
	str	r2, [r3, #32]
	ldmfd	sp!, {r3, lr}
	bx	lr
.L5:
	.align	2
.L4:
	.word	__bss_start__
	.word	__bss_end__
	.word	538968064
	.size	_cstart, .-_cstart
	.ident	"GCC: (GNU) 4.8.3"
