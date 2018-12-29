.globl _vectors
.globl _vectors_end
        
_vectors:
  ldr pc, _impossible_asm
  ldr pc, _impossible_asm
  ldr pc, _impossible_asm
  ldr pc, _impossible_asm
  ldr pc, _impossible_asm
  ldr pc, _impossible_asm
  ldr pc, _interrupt_asm
  ldr pc, _impossible_asm

_impossible_asm:              .word impossible_asm
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

impossible_asm:
  sub   lr, lr, #4
  push  {lr}
  push  {r0-r12}
  mov   r0, lr              @ Pass old pc
  bl    impossible_vector   @ C function
  pop   {r0-r12}
  ldm   sp!, {pc}^
