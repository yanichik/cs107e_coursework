/*
 * Reference full implementation of C start sequence for CS107E. This
 * function is called from start.s. _cstart() zeroes out the BSS
 * (assignment 4) and installs interrupt vectors (assignment 7). If main()
 * returns, it turns on the green ACT LED on the Raspberry Pi board.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 *
 * Date: 6/20/17
 */

// linker memmap places bss symbols at start/end of bss
extern int __bss_start__, __bss_end__;

// _vector and _vector_end are symbols defined in the interrupt
// assembly file, at the beginning and end of the vector and its embedded constants
extern int _vectors, _vectors_end;

extern void main();

// The C function _cstart is called from the assembly in start.s
// _cstart zeroes out the BSS section and then calls main.
// After main() completes, turns on the green ACT LED as
// a sign of successful execution.
void _cstart(void) {
    int *bss = &__bss_start__;
    int *bss_end = &__bss_end__;

    while (bss < bss_end) {
        *bss++ = 0;
    }

    static int * const RPI_INTERRUPT_VECTOR_BASE = 0x0;
    
    /* Copy in interrupt vector table and FIQ handler at end of table. */
    int* vectorsdst = RPI_INTERRUPT_VECTOR_BASE;
    int* vectors = &_vectors;
    int* vectors_end = &_vectors_end;
    while (vectors < vectors_end) {
        *vectorsdst++ = *vectors++;
    }

    main();

    // Turn on the green ACT LED (GPIO 47)
    volatile unsigned int *GPIO_FSEL4  = (unsigned int *)0x20200010;
    volatile unsigned int *GPIO_SET1 =   (unsigned int *)0x20200020;
    *GPIO_FSEL4 = (1 << ((47-40)*3));
    *GPIO_SET1 = (1 << (47-32));
}
