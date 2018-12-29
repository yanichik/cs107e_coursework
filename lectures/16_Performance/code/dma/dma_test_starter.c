#include "assert.h"
#include "printf.h"
#include "strings.h"
#include "system.h"
#include "timer.h"

// Section 4.2.1.1 of BCM2835-ARM-Peripherals.pdf
struct dma_cb {
	unsigned int TI;
	unsigned int SOURCE_AD;
	unsigned int DEST_AD;
	unsigned int TXFR_LEN;
	unsigned int STRIDE;
	unsigned int NEXTCONBK;
	unsigned int reserved1;
	unsigned int reserved2;
};

static volatile struct dma_cb dma_control __attribute__ ((aligned (256)));
static volatile unsigned *dma_base = (unsigned *) 0x20007000;

// -------------------------------------------------------------------
// Time Trial Helpers
// -------------------------------------------------------------------

// Our time trials will be using strings of this length.
#define COPYLEN (1 << 12)

unsigned _time_trial(char *(*cpy)(char *dst, const char *src))
{
    char src[COPYLEN] __attribute__ ((aligned (256)));
    char dst[COPYLEN] __attribute__ ((aligned (256)));

    for (int i = 0; i < COPYLEN; i++) {
        src[i] = 'X';   // populate src with X's
        dst[i] = (char) i + 1; // populate dest with some non-X values
    }
    src[COPYLEN-1] = '\0';

    unsigned start = timer_get_ticks();
    cpy(dst, src);
    unsigned ticks = timer_get_ticks() - start;

    assert(strcmp(src, dst) == 0);
    return ticks;
}

#define TIME_TRIAL(fn) do {           \
    printf("Running " #fn "... ");    \
    printf("took %d ticks\n", _time_trial(fn)); \
} while (0)


// -------------------------------------------------------------------
// Wicked fast strcpy functions to test
// -------------------------------------------------------------------

char *strcpy_naive(char *dst, const char *src)
{
    for (int i = 0; i <= strlen(src); i++) {
        dst[i] = src[i];
    }
    return dst;
}

int main() {
    timer_init();
    timer_delay(3);   // wait for uart/screen to catch up

    printf("Ready to start time trials!\n");

    TIME_TRIAL(strcpy_naive);

    printf("%c", 4); // Send EOT to signal done.
    return 0;
}
