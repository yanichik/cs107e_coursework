// configure GPIO 20 for output
ldr r0, FSEL2
mov r1, #1
str r1, [r0]

FSEL2: .word 0x20200008
