.globl _vectors
.globl _vectors_end
        
_vectors:
ldr pc, =impossible_asm
ldr pc, =impossible_asm
ldr pc, =impossible_asm
ldr pc, =impossible_asm
ldr pc, =impossible_asm
ldr pc, =impossible_asm
ldr pc, =interrupt_asm
ldr pc, =impossible_asm

_vectors_end:

interrupt_asm:
  sub   lr, lr, #4
  push  {lr}
  push  {r0-r12}
  mov   r0, lr              @ Pass old pc
  bl    interrupt_vector    @ C function
  pop   {r0-r12}
  ldm   sp!, {pc}^

impossible_asm:
  sub   lr, lr, #4
  push  {lr}
  push  {r0-r12}
  mov   r0, lr              @ Pass old pc
  bl    impossible_vector   @ C function
  pop   {r0-r12}
  ldm   sp!, {pc}^

