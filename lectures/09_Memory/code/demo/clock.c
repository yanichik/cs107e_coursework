#include "gpio.h"
#include "timer.h"

/* This is a comment */
#define DELAY 200


int square(int val)
{
    return val*val;
}

void blink(int pin)
{
    int n = square(13);

    gpio_set_output(pin);
    while (--n != 0) {
        gpio_write(pin, gpio_read(pin));
        timer_delay_ms(DELAY);
    }
}

void main(void)
{
    gpio_init();
    timer_init();
    blink(GPIO_PIN47);
}