#include "printf.h"
#include "timer.h"
#include "mailbox.h"

#define GPU_NOCACHE 0x40000000


typedef struct {
    unsigned int width;       // width of the display
    unsigned int height;      // height of the display
    unsigned int virtual_width;  // width of the virtual framebuffer
    unsigned int virtual_height; // height of the virtual framebuffer
    unsigned int pitch;       // number of bytes per row
    unsigned int depth;       // number of bits per pixel
    unsigned int x_offset;    // x of the upper left corner of the virtual fb
    unsigned int y_offset;    // y of the upper left corner of the virtual fb
    unsigned int framebuffer; // pointer to the start of the framebuffer
    unsigned int size;        // number of bytes in the framebuffer
} fb_config_t;

static volatile fb_config_t fb __attribute__((aligned(16)));

const int WIDTH = 640;
const int HEIGHT = 480;
const int DEPTH = 32;

int fb_init(void) {
    fb.width = fb.virtual_width = WIDTH;
    fb.height = fb.virtual_height = HEIGHT;
    fb.depth = DEPTH;
    fb.x_offset = 0;
    fb.y_offset = 0;

    fb.pitch = 0;
    fb.framebuffer = 0;
    fb.size = 0;

    mailbox_write(MAILBOX_FRAMEBUFFER, (unsigned)&fb + GPU_NOCACHE);
    int err =  mailbox_read(MAILBOX_FRAMEBUFFER);
    return err;
}

void main(void) {
    (void) fb_init();
    printf ("pitch (bytes): %d\n", (int)fb.pitch);
    printf ("height (pixels): %d\n", (int)fb.height);
    printf ("depth (bits): %d\n", (int)fb.depth);
    unsigned pitch = fb.pitch / 4; // bytes to words
    unsigned(*im)[pitch] = (unsigned(*)[pitch])fb.framebuffer;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < pitch; x++) {
            im[y][x] = 0xff0000ff;
        }
    }
}
