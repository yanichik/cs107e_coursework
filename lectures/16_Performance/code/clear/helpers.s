.globl assign8
assign8:
  // r3 -- caller-saved
  // r4, r5, r6, r7, r8, r10, r11 -- callee-saved
  push {r4, r5, r6, r7, r8, r10, r11}

  mov r3, r1
  mov r4, r1
  mov r5, r1
  mov r6, r1
  mov r7, r1
  mov r8, r1
  mov r10, r1
  mov r11, r1

loop:
  stm r0!, {r3, r4, r5, r6, r7, r8, r10, r11}
  subs r2, #1
  bne loop

  pop {r4, r5, r6, r7, r8, r10, r11}
  bx lr

