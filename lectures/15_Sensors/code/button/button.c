#include "timer.h"
#include "gpio.h"
#include "gpioextra.h"
#include "uart.h"
#include "printf.h"

int BUTTON = GPIO_PIN2;

void main(void) {
  unsigned prevbutton;

  timer_init();
  gpio_init();
  uart_init();
  
  gpio_set_input(BUTTON);
  gpio_set_pullup(BUTTON);
  
  prevbutton = gpio_read(BUTTON);
  while (1) {
      unsigned button = gpio_read(BUTTON);
      if( button != prevbutton ) {
          // 0 is pressed, 1 is released
          printf( button ? "released\n" : "pressed " );
          prevbutton = button;
      }
  }
}
