#include "gpio.h"
#include "gpioextra.h"
#include "uart.h"
#include "interrupts.h"
#include "ringbuffer.h"
#include "console.h"
#include "assert.h"

#define LINE_SIZE 40
#define BUTTON_PIN GPIO_PIN25

static int npresses = 0;

void wait_for_press(void) {
    while (gpio_read(BUTTON_PIN) == 0) {}
    while (gpio_read(BUTTON_PIN) == 1) {}
    npresses++;
}

void main() {
    unsigned int index = 0;
    char line[LINE_SIZE];
    line[0] = 0;

    gpio_init();
    console_init(40, 40);
    uart_init();

    gpio_set_input(BUTTON_PIN);
    gpio_set_pullup(BUTTON_PIN);

    while (1) {
        wait_for_press();
        line[index] = '+';
        line[++index] = 0;
        if (index >= 60) {
            index = 0;
        }
        console_printf("Button pushes: %s\n", line);
    }
}
