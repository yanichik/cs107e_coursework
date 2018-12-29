#include "timer.h"
#include "gl.h"
#include "printf.h"

// The top 7 bars: the last bar is a little wide, so it
// has two entries in the 8 entry array.
static unsigned int bars[] = {0xFFC0C0C0,
                              0xFF00C0C0,
                              0xFFC0C000,
                              0xFF00C000,
                              0xFFC000C0,
                              0xFF0000C0,
                              0XFFC00000,
                              0XFFC00000
                             };

// The 7 castellations in the middle. The last bar is a little
// wide, so it has two entries in the 8 entry array.
static unsigned int castellations[] = {0xFFC00000,
                                       0xFF131313,
                                       0xFFC000C0,
                                       0xFF131313,
                                       0xFFC0C000,
                                       0xFF131313,
                                       0xFFC0C0C0,
                                       0xFFC0C0C0
                                      };

void cbars() {
    for (int i = 0; i < 7; i++) {
        gl_draw_rect(i * 180, 0, 180, 720, bars[i]);
        gl_draw_rect(i * 180, 720, 180, 48, castellations[i]);
    } // last bar is a little wider
    gl_draw_rect(7 * 180, 0, 20, 720, bars[7]);
    gl_draw_rect(7 * 180, 720, 20, 48, castellations[7]);

    gl_draw_rect(0, 768, 112, 192, 0xFF4A2100);
    gl_draw_rect(112, 768, 336, 192, 0xFFFFFFFF);
    gl_draw_rect(448, 768, 224, 192, 0xFF7A0032);
    gl_draw_rect(672, 768, 228, 192, 0xFF131313);
    gl_draw_rect(900, 768,  60, 192, 0xFF000000);
    gl_draw_rect(960, 768,  60, 192, 0xFF131313);
    gl_draw_rect(1020, 768,  60, 192, 0xFF262626);
    gl_draw_rect(1080, 768, 200, 192, 0xFF131313);
}

void main(void) {
    gl_init(1280, 960, GL_SINGLEBUFFER);
    cbars();
}

