#include "gpio.h"
#include "keyboard.h"
#include "gl.h"

#define MAXLINE 80

char line[MAXLINE];
unsigned int index = 0;

void read_char_from_keyboard()
{
    int ch = keyboard_read_next();
    if (index < MAXLINE) {
      line[index++] = ch;
      line[index] = '\0';
    }
}

void update_screen()
{
    gl_clear(GL_BLACK);
    gl_clear(GL_BLUE);
    gl_clear(GL_WHITE);
    gl_clear(GL_RED);
    gl_draw_string(20, 20, line, GL_WHITE);
    gl_swap_buffer();
}

void main(void) 
{
  gpio_init();
  keyboard_init();
  line[index] = '\0'; // initialize buffer

  gl_init(1280, 1024, GL_DOUBLEBUFFER);

  gl_draw_string(0, 0, "Waiting...", GL_WHITE);
  gl_swap_buffer();

  while (1) {
      read_char_from_keyboard();
      update_screen();
  }
}
