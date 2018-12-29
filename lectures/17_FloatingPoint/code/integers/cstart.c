#define GPIO_FSEL4  ((unsigned int *)0x20200010)
#define GPIO_SET1   ((unsigned int *)0x20200020)
#define GPIO_CLR1   ((unsigned int *)0x2020002c)

// Green ACT LED is GPIO 47.
#define SUCCESS_OUTPUT (1 << (3*7))
#define SUCCESS_BIT    (1 << (47-32))

extern int __bss_start__;
extern int __bss_end__;

extern void main();

// Zeroes out the BSS before calling main.
// Turns on the green ACT LED when done, to show successful completion.
// This function is called from start.s.
void _cstart() {
    int *bss = &__bss_start__;
    int *bss_end = &__bss_end__;

    while (bss < bss_end) {
        *bss++ = 0;
    }

    main();

    // Turn the green ACT LED (GPIO 47).
    *GPIO_FSEL4 = SUCCESS_OUTPUT;
    *GPIO_SET1 = SUCCESS_BIT;
}
