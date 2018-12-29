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

char *strcpy_one_strlen(char *dst, const char *src)
{
    int slen = strlen(src);
    for (int i = 0; i <= slen; i++) {
        dst[i] = src[i];
    }
    return dst;
}

char *strcpy_memcpy(char *dst, const char *src)
{
    memcpy(dst, src, COPYLEN);
    dst[COPYLEN-1] = '\0';
    return dst;
}

char *strcpy_dma(char *dst, const char *src)
{
	dma_control.TI = (1 << 8) | (1 << 4);
	dma_control.SOURCE_AD = (unsigned) src;
	dma_control.DEST_AD = (unsigned) dst;
	dma_control.TXFR_LEN = COPYLEN;            // total number of bytes
	dma_control.STRIDE = 0;
	dma_control.NEXTCONBK = 0;

	*dma_base = 1<<31;                         // reset dma
	*(dma_base + 1) = (unsigned) &dma_control; // tell dma where we are
	*dma_base = 1;                             // start dma
	while(*(dma_base + 1) != 0) { ; }          // wait until dma is finished

    return dst;
}

int main() {
    timer_init();
    timer_delay(3);   // wait for uart/screen to catch up

    printf("Ready to start time trials!\n");

    TIME_TRIAL(strcpy_naive);
    TIME_TRIAL(strcpy_one_strlen);
    TIME_TRIAL(strcpy_memcpy);
    TIME_TRIAL(strcpy_dma);

    printf("\nCaching turned on!\n\n");
    system_enable_cache();

    TIME_TRIAL(strcpy_naive);
    TIME_TRIAL(strcpy_one_strlen);
    TIME_TRIAL(strcpy_memcpy);
    TIME_TRIAL(strcpy_dma);

    printf("%c", 4); // Send EOT to signal done.
    return 0;
}
