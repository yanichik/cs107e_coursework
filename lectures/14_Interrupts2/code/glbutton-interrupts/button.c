#include "gpio.h"
#include "gpioextra.h"
#include "uart.h"
#include "interrupts.h"
#include "ringbuffer.h"
#include "console.h"
#include "assert.h"

#define LINE_SIZE 40
#define BUTTON_PIN GPIO_PIN25

static rb_t* rb;

void button_pressed(unsigned int pc) {
    rb_enqueue(rb, pc);
    gpio_clear_event(BUTTON_PIN);
}

void main() {
    unsigned int index = 0;
    char line[LINE_SIZE];
    line[0] = 0;
    int last_pc = 0;

    rb = rb_new();

    gpio_init();
    console_init(40, 40);
    uart_init();

    gpio_set_input(BUTTON_PIN);
    gpio_set_pullup(BUTTON_PIN);
    gpio_enable_event_detection(BUTTON_PIN, GPIO_DETECT_FALLING_EDGE);
    bool ok = interrupts_attach_handler(button_pressed);
    assert(ok);
    interrupts_enable_source(INTERRUPTS_GPIO3);

    interrupts_global_enable();

    while (1) {
        if( !rb_empty(rb) ) {
            rb_dequeue(rb, &last_pc );
            line[index] = '+';
            line[++index] = 0;
            if (index >= 60) {
                index = 0;
            }
            console_printf("Button pushes: %s\nLast PC: %x\n", line, last_pc);
        }
    }
}
