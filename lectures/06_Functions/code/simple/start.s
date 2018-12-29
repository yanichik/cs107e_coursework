// _start is entry point
.global _start
_start:
    mov sp,#0x8000000  // set up stack pointer
    bl _cstart        	// call _cstart
hang: b hang        	// after _cstartreturns, go into infinite loop
