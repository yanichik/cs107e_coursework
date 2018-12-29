#include "gpio.h"
#include "keyboard.h"
#include "uart.h"
#include "printf.h"


void main(void) 
{
    gpio_init();
    keyboard_init();
    uart_init();

    while (1) {
        unsigned char seq[3];
        int len = keyboard_read_sequence(seq);
        printf("Scan code sequence: ");
        for (int i = 0; i < len; i++)
            printf("%02x ", seq[i]);
        // if last scan code of sequence corresponds to printable ascii char, show it
        unsigned char ch = ps2_keys[seq[len-1]].ch;
        if (ch >= ' ' && ch <= '~') printf("(ascii '%c')", ch);
        printf("\n");
    }
}
