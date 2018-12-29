---
layout: page
title: Guide to compiling for your native environment
---

On rare occasion you may find it useful to compile and run your code locally
instead of on the Pi. This is really only true for assignment 3 in this course,
so this guide will show you how to compare your printf against the one on your
machine.

Since your printf will depend on uart, we need to replace the libpi uart
implementation with our own. Create a file `uart_native.c` like so:


```c
#include "uart.h"
#include <stdio.h>

void uart_init() {}

int uart_getchar() { 
    return getchar();
}

int uart_putchar(int c) {
    putchar(c);
    return c;
}

void uart_flush() {
    fflush(stdout);
}
```

This tells all the uart functions to call normal POSIX output-generating
functions (note this only works on POSIX-compliant systems like Linux
distributions and OS X, not Windows). Then we need to define a file that
will test our printf along with the system one in `stdio.h`. Create a file
`test_native.c`:

```c
#include <stdio.h>
#include "my_printf.h"

#define BUF_SIZE 100

int main() {
  char buf[BUF_SIZE];
  my_snprintf(buf, BUF_SIZE, "Hello, world!"); // your implementation of snprintf
  printf("%s\n", buf); // system implementation of printf
}
```

The tricky part here is that in order to use both the system printf and your
printf in the same code, we have to change your printf's name so it doesn't
conflict. To do this, we can use the C preprocessor to alias all the public
functions in printf.c to add the prefix "my_", e.g. `printf` -> `my_printf`.
We will accomplish this by adding rules to our Makefile:

```
CFLAGS_NATIVE = -I$(CS107E)/include -g -Wall -std=c99
ALIASES = -D vsnprintf=my_vsnprintf -D snprintf=my_snprintf -D printf=my_printf
my_printf.h:
	gcc $(CFLAGS_NATIVE) $(ALIASES) -E $(CS107E)/include/printf.h -o $@
printf_native.o: printf.c
	gcc $(CFLAGS_NATIVE) $(ALIASES) printf.c -c -o $@
test_native.bin: my_printf.h printf_native.o
	gcc $(CFLAGS_NATIVE) test_native.c uart_native.c printf_native.o \
		-o test_native.bin
native: test_native.bin
```

Then you can run `make native` and get an executable `test_native.bin` that
you can run on your own computer, e.g.

```
$ ./test_native.bin
Hello, world!
```

Be careful of the limitations of this approach. The native compilation method
is useful for quickly visually inspecting the outputs of your functions, but
if you're debugging memory issues then issues may present themselves in
different ways than on the Pi, and reading the assembly in tools like gdb will
be challenging since it's not ARM.
