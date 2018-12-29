#include "gpio.h"
#include "gpioextra.h"
#include "uart.h"
#include "interrupts.h"
#include "ringbuffer.h"
#include "printf.h"
#include "assert.h"

static const int BUTTON = GPIO_PIN25;

/*
static void button_press(unsigned int pc) {
}
*/

/*
static void setup_interrupts(void) {
    gpio_enable_event_detection(BUTTON, GPIO_DETECT_FALLING_EDGE);
    bool ok = interrupts_attach_handler(button_press);
    assert(ok);
    interrupts_enable_source(INTERRUPTS_GPIO3);
    interrupts_global_enable();
}
*/

static void button_init(void)
{
}

static void button_test(void)
{
}

void main(void) {
    gpio_init();
    uart_init();
    button_init();

    while (1) {
       /* ... */
    }
}
