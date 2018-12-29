#include "gpio.h"
#include "gpioextra.h"
#include "uart.h"

const int CLK = GPIO_PIN23;
const int DATA = GPIO_PIN24;

void wait_for_falling_clock_edge() {
  while(gpio_read(CLK) == 0) {}
  while(gpio_read(CLK) == 1) {}
}

void main(void) {
    gpio_init();
    uart_init();

    gpio_set_input(CLK);
    gpio_set_pullup(CLK);

    gpio_set_input(DATA);
    gpio_set_pullup(DATA);

    while (1) {
        for( int i = 0; i < 11; i++ ) {
            wait_for_falling_clock_edge();
            uart_putchar(gpio_read(DATA) ? '1' : '0');
        }
        uart_putchar('\n');
    }
}
