---
layout: page
title: Guide to Make for ARM cross-development
---

*Written for CS107E by Anna Zeng, edited by Michelle Park*

Make is a tool that automates building executable programs;
a makefile is a file that tells `make` what to do in order to build
the programs you want. As you will see soon enough, they make life
as a computer science student a whole lot smoother!

In this guide, we'll learn about using makefiles
for cross-development on the ARM architecture.
We will briefly review makefile syntax and usage.
For additional information about makefiles,
check out the 
[CS107 Guide to Makefiles](http://cs107.stanford.edu/guide/make.html)
and other resources on the bottom of the page.

Below is a simple makefile used
to build a binary for the ARM processor.
Many of our labs and assignments will include similar makefiles, 
so you will soon become familiar with this makefile structure.

```
    NAME = blink

    CFLAGS = -g -Wall -Og -std=c99 -ffreestanding
    LDFLAGS = -nostdlib

    all: $(NAME).bin
     
    %.bin: %.elf
        arm-none-eabi-objcopy $< -O binary $@

    %.elf: %.o
        arm-none-eabi-gcc $(LDFLAGS) $< -o $@

    %.o: %.c
        arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
    
    %.list: %.o
        arm-none-eabi-objdump -d $< > $@

    install: $(NAME).bin
        rpi-install.py $<

    clean:
        rm -f *.o *.elf *.bin *.list
```

This Makefile may look a bit cryptic at first! Let's try breaking it down step by step.

### Makefile Basics: Rules

From lecture, we were introduced to Makefiles as an improvement on the `doit` script.
A very simple Makefile could be written like this:
    
    all: button.bin
    
    button.bin: button.c
        arm-none-eabi-gcc -Og -g -Wall -std=c99 -ffreestanding -c button.c -o button.o
        arm-none-eabi-objcopy button.o -O binary button.bin
    
    clean: 
        rm -f  *.bin *.o

__Rules__ are written in the following way: "you require __dependencies__ on the right-hand-side
to make our __target__ on the left-hand-side." Thus, in this makefile, the first line
indicates: "you require `button.bin` to make `all`." In other words, to make `all`, we need to first make `button.bin`.
    
    all: button.bin

This brings us to the next rule, which tells us how to make `button.bin`. You may interpret this as
requiring certain ingredients (dependencies on the right-hand-side)
to create the thing you want (target on the left-hand-side).

    button.bin: button.c

The text that immediately follows the rule, called the __recipe__ for the rule,
are commands necessary to turn the ingredients (`button.c` in this case)
into the final product (`button.bin` in this case).
We also throw in a comment to explain the additional flags included with our call to `arm-none-eabi-gcc`.

(Yes, comments in makefiles are denoted with `#`.)

    # Here, we set compile flags for gcc:
    #  -std=c99        use the c99 standard
    #  -Og             generate optimized code designed for debugging
    #  -g              add debugging information
    #  -Wall           give warnings about *all* issues
    #  -ffreestanding  generate code assuming no operating system

    button.bin: button.c
        arm-none-eabi-gcc -std=c99 -Og -g -Wall -ffreestanding -c button.c -o button.o
        arm-none-eabi-objcopy button.o -O binary button.bin

The line below indicates what should happen when we `make clean`; the keyword `clean` tells Make to run the command below.

    clean: 
        rm -f *.bin *.o


### Makefile Magic: Macros & More Rules

After copy-pasting and editing every Makefile each time a new program is created,
we have finally decided that it's time to be even more efficient.
After all, Makefiles are written for convenience!

```
    NAME = blink
    ARM = arm-none-eabi
    CFLAGS  = -std=c99 -Og -g -Wall -ffreestanding
    LDFLAGS = -nostdlib

    all: $(NAME).bin

    $(NAME).bin: $(NAME).c
        $(ARM)-gcc $(CFLAGS) -c $(NAME).c -o $(NAME).o
        $(ARM)-gcc $(LDFLAGS) $(NAME).o -o $(NAME).elf
        $(ARM)-objcopy $(NAME).elf -O binary $(NAME).bin
    
    clean: 
        rm -f *.list *.bin *.o
```
So we've just added three __macros__ up top. They're similar to variables
in that they replace instances of the macro throughout the file with their assigned text.
Be sure to use the `$(<macro_name>)`
syntax to access the value of the macro and allow string concatenation.
(Did you see what we did there with the `ARM` macro?)
Phew, this saves us a lot of visual space!

Now, let's generalize the rules so that they can be used to build a program from any assembly or C file, without hard-coding the rules to the filename `blink`.

```
    # This general rule compiles a C program into an object file.
    # filename.o is built from filename.c
    %.o: %.c
        $(ARM)-gcc $(CFLAGS) -c $< -o $@

    # This general rule converts assembly instructions into an object file.
    # filename.o is built from filename.s
    %.o: %.s
        $(ARM)-as $(CFLAGS) $< -o $@

    # This general rule links an object file into an executable ELF file.
    # filename.elf is built from filename.o
    %.elf: %.o
        $(ARM)-gcc $(LDFLAGS) $< -o $@

    # This general rule extract binary from an ELF executable
    # filename.bin is built from filename.elf
    %.bin: %.elf
        $(ARM)-objcopy $< -O binary $@
```

The symbols that begin with `$` and `%` are handled by `make` using the following interpretations:

* `%` is a wildcard symbol when used in a rule; `%.o` for example matches any file that ends with `.o`
* `$@` refers to the left part of the rule, before the `:`
* `$<` refers to the first element in the right part of the rule, after the `:`

One more special variable `$^` refers to all elements in the right part of the rule, after the `:`, which is to say all of the dependencies.

So, really, you can think of the makefile as a big cookbook that culminates in the program you ultimately wish to create.

For convenience, we can also throw in another rule so we don't have to type in `rpi-install.py blink.bin`
every time we want to run our program on the Pi.

    # The install target uploads a freshly made binary image to rpi bootloader
    install: $(NAME).bin
        rpi-install.py $<

Congratulations! You are now a makefile wizard!✨

If you'd like to learn more, check out
[a Makefile tutorial](http://www.opussoftware.com/tutorial/TutMakefile.htm),
[another Makefile tutorial](http://www.delorie.com/djgpp/doc/ug/larger/makefiles.html),
the
[CS107 Guide to Makefiles](http://cs107.stanford.edu/guide/make.html),
and the
[GNU Documentation about Compiler Options](https://gcc.gnu.org/onlinedocs/gcc-4.2.2/gcc/C-Dialect-Options.html).
