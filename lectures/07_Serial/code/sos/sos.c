#include "gpio.h"
#include "timer.h"

#define PIN 20
#define ONE_SECOND 1000
#define DELAY_MORSE (ONE_SECOND/4)

void morse_s();
void morse_o();
void dot();
void dash();
void morse_letter(char *code); // "--..-."

void dot() {
    gpio_write(PIN,1);
    timer_delay_ms(DELAY_MORSE);
    gpio_write(PIN,0);
    timer_delay_ms(DELAY_MORSE);
}

void dash() {
    gpio_write(PIN,1);
    timer_delay_ms(DELAY_MORSE * 3);
    gpio_write(PIN,0);
    timer_delay_ms(DELAY_MORSE);
}

void morse_s() {
    morse_letter("...");
}

void morse_o() {
    morse_letter("---");
}

void morse_letter(char *code) {
    while (*code) {
        *code++ == '.' ? dot() : dash();
    }
}

void main(void) {
    timer_init();
    gpio_init();
    gpio_set_output(PIN);

    while (1) {
        // flash SOS
        morse_s();
        morse_o();
        morse_s();
        timer_delay_ms(DELAY_MORSE * 4);
    }
}
