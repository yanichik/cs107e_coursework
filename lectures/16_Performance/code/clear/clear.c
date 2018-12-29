#include "printf.h"
#include "fb.h"
#include "assert.h"
#include "system.h"
#include "timer.h"

#define _WIDTH 640
#define _HEIGHT 512
#define _DEPTH 4

struct pixel {
    unsigned char b, g, r, alpha;
};
typedef volatile struct pixel pixel_t;

static pixel_t *fb;

// Writes v to the R, G, and B of each pixel in framebuffer.
void write_screen(unsigned char v) {
    for (volatile unsigned i = 0; i < fb_get_width() * fb_get_height(); i++) {
        pixel_t *p = &fb[i];
        p->r = p->g = p->b = v;
        p->alpha = 0xff;
    }
}


#define TIME(cmd, val, iter) do {                       \
        printf("----------\n");                         \
        printf("running: " #cmd "\n");                  \
        int i;                                          \
        for (i = 0; i < iter; i++) {                    \
            unsigned start = timer_get_ticks();          \
            cmd(0x00);                                  \
            cmd(val);                                   \
            unsigned total = timer_get_ticks() - start;  \
            printf("took %d ticks\n", total);           \
        }                                               \
    } while (0)

void main() {
    //printf_init();
    timer_init();

    fb_init(_WIDTH, _HEIGHT, _DEPTH, 0);
    fb = (struct pixel *) fb_get_draw_buffer();

    TIME(write_screen, 0xff, 4);

    printf("%c", 4); // Send EOT to signal done.
}
