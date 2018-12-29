.globl _start
_start:
    mov sp, #0x8000000
    bl _cstart
hang: b hang
