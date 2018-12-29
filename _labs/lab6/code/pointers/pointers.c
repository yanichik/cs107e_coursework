#include "gpio.h"
#include "uart.h"
#include "printf.h"

void main(void)
{
    gpio_init();
    uart_init();

    // Basic pointer review: What's the difference between incrementing a `char
    // *` and a `unsigned int *`?
    printf("Pointer review:\n");
    printf("===============\n");
    char *char_ptr = "Hello";
    unsigned int uint_arr[] = {0, 1, 2};
    unsigned int *uint_ptr = uint_arr;

    printf("char_ptr = %08x\n", (unsigned) char_ptr);
    printf("char_ptr+1 = %08x\n", (unsigned) (char_ptr + 1));

    printf("uint_ptr = %08x\n", (unsigned) uint_ptr);
    printf("uint_ptr+1 = %08x\n", (unsigned) (uint_ptr + 1));

    printf("\n");
    // What happens if we walk off the end of the array?
    printf("Walking off the end of the array uint_arr: \n");
    for (int i = 0; i < 4; ++i) {
        printf("[%d] = %08x ", i, (unsigned) (uint_ptr[i]));
    }
    printf("\n");
    printf("\n");

    printf("Pointers to pointers example\n");
    const char *tokens[2];
    tokens[0] = "Hello";
    tokens[1] = "World";
    printf("tokens = %08x\n", (unsigned) tokens);
    printf("tokens+1 = %08x\n", (unsigned) (tokens + 1));
    printf("tokens[0] = %08x\n", (unsigned) tokens[0]);
    printf("tokens[1] = %08x\n", (unsigned) (tokens[1]));
    printf("*tokens[0] = %08x\n", (unsigned) *tokens[0]);
    printf("*tokens[1] = %08x\n", (unsigned) (*tokens[1]));
    printf("**tokens = %08x\n", (unsigned) **tokens);
    printf("**(tokens + 1) = %08x\n", (unsigned) (**(tokens + 1)));


    printf("===============\n");
    printf("\n");

    // multi-dimensional arrays and pointers
    printf("Multi-dimensional arrays and pointers\n");
    printf("=====================================\n");
    int a[2][2] = { {0, 1}, {2, 3} };
    int *b = &a[0][0];
    int (*c)[2] = a;
    int (*d)[2][2] = &a;

    printf("a = %08x\n", (unsigned)a );
    printf("&a[0][0] = %08x\n", (unsigned)(&a[0][0]) );
    printf("&a[0][1] = %08x\n", (unsigned) &a[0][1]);

    printf("b = %08x\n", (unsigned)b );
    printf("b+1 = %08x\n", (unsigned)(b+1) );
    printf("b+2 = %08x\n", (unsigned)(b+2) );
    printf("&a[0] = %08x\n", (unsigned)(&a[0]) );
    printf("&a[1] = %08x\n", (unsigned)(&a[1]) );
    printf("c = %08x\n", (unsigned)c );
    printf("c+1 = %08x\n", (unsigned)(c+1) );
    printf("d = %08x\n", (unsigned)d );
    printf("d+1 = %08x\n", (unsigned)(d+1) );

    printf("=====================================\n");
    printf("\n");

    // single dimensional arrays and pointers
    printf("Single-dimensional arrays and pointers\n");
    printf("======================================\n");
    int f[] = { 0, 1 };
    int g[] = { 2, 3, 4 };
    // will the following work?
    // int *h = {2, 3, 4};
    printf("f = %08x\n", (unsigned)f );
    printf("g = %08x\n", (unsigned)g );

    int *p[2] = { f, g };
    int *q = p[0];
    printf("p = %08x\n", (unsigned)p );
    printf("q = %08x\n", (unsigned)q );
    printf("p[0] = %08x\n", (unsigned)p[0] );
    printf("p[1] = %08x\n", (unsigned)p[1] );

    printf("======================================\n");

    printf("%c", 4); // Send end of transmission to rpi-install.py
}
