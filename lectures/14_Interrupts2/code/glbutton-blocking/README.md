Program that displays button pushes (GPIO25) on the display.
GPIO25 should be wired to ground through a button (it is
configured to be pullup).

Goal is to show that a slow refresh can cause you to
miss presses. Note that the standard reference gl.c
implementation is fast enough that it's not super-obvious;
I recommend slowing down gl_clear() to make it obvious.

Author: Philip Levis <pal@cs.stanford.edu>
Date: 5/18/17
