---
layout: page
title: 'Assignment 2: Implement a Clock'
permalink: /assignments/assign2/
released: true
toc: true
---

*Written by Pat Hanrahan; updated by Julie Zelenski*

**Due: Wednesday, October 17, 2018 at 11:30 AM**

### Goals
Your next assignment is to build a 'clock' using a 4-digit 7-segment
display.

The goals of this assignment are for you to:

- Understand bare metal programming in C on the Raspberry Pi.
- Start building a simple, modular library of useful functions.
- Learn how to write and use automated test cases to validate your program's behavior.
- Learn how to use the Raspberry Pi's system timer peripheral.
- Understand how to refresh a 4-digit 7-segment display.

### Get started

The starter code for this assignment is deployed slightly differently than
previous assignments.  This time, you will just check out the
`assign2-basic` branch which has already been created for you:

```
$ cd cs107e_home/assignments
$ git fetch origin
$ git checkout assign2-basic
$ ls
Makefile apps     cstart.c gpio.h   start.s  timer.c
abort.c  assert.h gpio.c   memmap   tests    timer.h
```

Familiarize yourself with the starter code and review the provided Makefile. The project also includes a few [magic files](#magic) (`memmap`, `start.s`, and `cstart.c`) that are necessary for C programs. We will be explaining their purpose in the upcoming lectures.

### Modular design

For this assignment, you will implement functions
across three different C files: `gpio.c`, `timer.c`, and `apps/clock.c`.  The first two files implement reusable modules, the latter is the application program file.

These modules provide access to two of the Raspberry Pi peripherals. The `gpio` module has routines that control the GPIO pins and the `timer` module retrieves the system tick count. You will use these modules when building your clock application, but more broadly, these modules are intended to be reusable in any future application which requires similar functionality. These two modules are the first of many more to come. By the end of the quarter, you will have implemented a complete set of modules that you can package into a library of reusable Raspberry Pi functions.

A module is divided into an _interface_ and its _implementation_. The module's header file, e.g. `gpio.h` or `timer.h`, defines the interface. The interface details the functionality that is exported by the module. Each public function is listed with its name, prototype, and documentation about what the function does. The corresponding `.c` file will contain the implementation of the functions. We provide the module interface; it will be your job to write the module implementation.

The module interfaces are given in `gpio.h` and `timer.h`. You are not to change anything in these header files. All your edits will be in the corresponding C files. You shouldn't expose additional public `gpio_` or `timer_` functions. However, you can add your own private helper functions by declaring those functions at the top of the C file with the `static` keyword to make them only accessible to the implementation. 

The file `apps/clock.c` contains your application program code that configures and operates your clock. The clock code will not directly manipulate the gpio and timer peripherals, instead it will call on the functions exported from the gpio and timer modules. There is no required interface for the clock application, but you should strive for a clean and well-decomposed design that would make your CS106 section leader proud.

The subsequent assignments in CS107e will be structured on similar lines. Each week you will be implementing new module(s) to add your Raspberry Pi library in the context of an application program that uses those modules.

### Testing <a name="testing"></a>

Now that you're writing larger programs, we want to introduce you to
more sophisticated ways to test your program than in assignment 1. We
hope these ideas will serve you well throughout your programming life.

The starter project includes an additional program file `tests/test_clock.c` that
defines an alternate `main()` function. Instead of running the clock, this `main()` function makes a series of calls to `gpio` and `timer` functions and uses  `assert()` in order to validate the operations work correctly. You can run the test program by running `make test`.

Recall from Lab 2 how `assert()` drives the red and green LEDs
on the Pi as a simple status indicator. If an assert fails, the program
halts and blinks the red LED of doom. If all asserts succeed, 
the program completes normally and the green LED of happiness will turn on. Your goal is to make that little green light shine!

The given `tests/test_clock.c` has some very simple tests. You will extend the test program
with additional tests of your own so as to thoroughly exercise the
functionality of your modules. _Unit-testing_ each module in isolation before
going on to integrate its use into an application is an important strategy for
taming the complexity of these larger programs.  The additional tests you add
to `tests/test_clock.c` will be used to determine a portion of your grade for this assignment (that is,
to get full credit on this assignment, you will need to include a thorough
suite of tests as part of your submission).

### Basic part: a simple clock

#### 1. Wire up clock hardware 

The first step is to establish your hardware.

+ Complete the breadboard for the 4-digit 7-segment display you started in [Lab 2](/labs/lab2). Be sure to test your breadboard with jumper cables so that you know the wiring is correct before you connect it to the Raspberry Pi. 
+ Connect the Raspberry Pi GPIO pins 20-26 to the 1K current limiting
resistors that drive the segments A, B, C, D, E, F, G on your breadboard. An 8th pin, GPIO 27, can be used to control the decimal point, which is optional. 
+ Connect GPIO pins 10-13 to the base of the transistors controlling digits
1-4. 
+ At this point if you output 3.3V on GPIO 20 and 3.3V on GPIO 10, you should turn on segment A of digit 1. Hooray!
+ Take a picture of your finished hardware setup and commit to your repo. We want to see your beautiful handiwork!

#### 2. Implement gpio module

Review the documentation in `gpio.h` so you understand the module as a whole and the expected behavior of each function. 

The implementation of this library will require proper understanding of the
`volatile` keyword.  Remember from lecture that the `volatile` keyword
indicates to the compiler that the value of the variable could change
unexpectedly. Consider the variables that point to the memory-mapped peripheral
registers used to control the GPIO pins.  If you set a GPIO pin to input mode,
then the value of the Level register will depend on what is connected to the
pin.  The compiler cannot make any assumptions about the value of a variable
pointing to the Level register, and instead it should read the register every
time the program requests its value.  Again, the `volatile` keyword is only
appropriate when the value of the variable can change unexpectedly, so it's
considered bad style to mark variables as `volatile` that does not need to be. 
Furthermore, this prevents your compiler from making optimizations, so
extraneous `volatile` keywords can reduce performance.

We recommend that the first operations you implement are  `gpio_set_function` and `gpio_get_function`.  The [Broadcom BCM2835 peripheral manual](https://cs107e.github.io/readings/BCM2835-ARM-Peripherals.pdf#page=92) documents the GPIO function select registers and GPIO functions. For the clock, we will be using only `GPIO_FUNC_INPUT` and `GPIO_FUNC_OUTPUT`, but make sure
`gpio_set_function` works for all GPIO functions (they will be automatically tested during grading). Also note that 
`gpio_set_function` can be called multiple times with different pins. Each call affects only the pin passed
in as an argument; the function of all other pins should be unchanged.

In addition to properly handling any valid call, your functions should also be robust against client error. If asked to set an invalid pin or function, your function should detect and ignore the request, rather than blunder on with wrong or broken behavior. The function documentation in the module interface gives specific guidance on the expected handling for improper calls.

Next, implement `gpio_set_input` and `gpio_set_output` using
`gpio_set_function` to set a pin as an input or output pin.

Before moving on, test what you've implemented. Edit the `main()` function of `tests/test_clock.c` to uncomment the call to `test_gpio_set_get_function()`.  Run `make test` to see the result of executing these tests. If the green LED on the Pi turns on, all tests ran
successfully -- bravo! If you see the red LED blinking, this means
you are failing a test.  If neither LED lights up, your program may be freezing or
crashing somewhere during the tests.

If you don't get the green light, comment out each individual assert within   `test_gpio_set_get_function()`,
add them back one-by-one, and re-run to determine which specific test is
failing. Use that information to narrow in on your bug, fix it,
and re-test until you achieve green light nirvana.

Now review the given test cases and consider what **isn't**
covered. For example, what about testing alternate GPIO functions
or GPIO pins across the full range of 54? Add tests of your own to
validate these options. Re-run to verify that you also pass
your new tests before moving on.

The remaining two functions of the gpio module to implement are `gpio_write` and `gpio_read`. The `gpio_write` function accesses the SET and CLR device registers to turn pins on and off. Which device register does `gpio_read` access to get the current pin state?  Hint: Check the
[Broadcom BCM2835 peripheral manual](https://cs107e.github.io/readings/BCM2835-ARM-Peripherals.pdf#page=90).

Once you've implemented these functions, test them by uncommenting the call to
`test_gpio_read_write()` in the `main()` function of `tests/test_clock.c`. Re-run the test
program and make sure you get the green light. 

Now you should add further test cases of your own to verify that your functions work
correctly in all situations.  Think critically about what combinations of
function calls to your `gpio` module could introduce buggy behavior. For
example, what should happen when you call `gpio_set_function` twice on adjacent pins?
Remember that the tests we provided in the starter code are not comprehensive,
and, in particular, do not include test cases that are used by the automated
tester used for grading.

When testing, be sure to note that some special GPIO pins that exhibit
different behavior than the others. GPIO pins 14 and 15 are used for serial
transmission and will by default have the function `GPIO_FUNC_ALT5`.  You do
not need to include them in your tests. GPIO 35 controls the red power LED on
the Pi so if you change the function of the pin or clear it, the light will
turn off.

Congratulations, you've just completed your first Raspberry Pi module!

#### 3. Display a digit

In `apps/clock.c`, create an array of 16 elements, one for each
hexadecimal value between 0 and 15. Each array element should
be a byte (8-bits). Bit 0 (the least significant) will represent
segment A, bit 1 segment B, and so on. If a bit is set, then that
segment should be lit. For example, digit `0` consists of segments A-F, so its bit pattern is `0b00111111`. Digit `1` consists of just segments B and C, so its bit pattern is `0b00000110`.  (`0b` is what you put in front of a binary number
literal, just as you'd put `0x` in front of a hexadecimal
literal.)

Bit 7 (the most significant) will be used to represent `DP`, the dot. Since we won't be
using the dot in this assignment, bit 7 should always be 0.

Create bit patterns for all the digits 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
A, B, C, D, E, F. You won't be displaying A-F for this assignment, but they
may be useful in the future. 

Test this part by adding code to the `main()` function of `apps/clock.c` to display a single digit. Verify that your bit patterns are correct by displaying each digit value from `0` to `9`. 

#### 4. Implement timer module

In order to implement a clock, we'll need some way to determine the passage 
of time. Thankfully, the Raspberry Pi includes a "system timer". The system timer is an on-board peripheral that is initialized to zero when the Pi powers up and is 
continuously incremented once every microsecond behind the scenes.

Implement the `timer_get_ticks` function in `timer.c` to fetch
the current system tick count from the system timer. Chapter 12 of the
[Broadcom BCM2835 Peripherals Manual](http://www.raspberrypi.org/wp-content/uploads/2012/02/BCM2835-ARM-Peripherals.pdf#page=172)
contains the documentation for the system timer peripheral.

Note that, for this assignment, we only care about the lower
32-bits of the system timer. Don't forget that we use
[ARM physical addresses](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf#page=6),
not bus addresses (0x7E... for peripherals), so you'll need to
change the 0x7E... prefix in any peripheral address to 0x20.

Now you can uncomment the call `test_timer()` in `tests/test_clock.c`. You
should be passing all our module tests now -- super! Now you're ready to implement the rest of the clock application.

#### 5. Write display refresh loop

GPIO pins 20 to 26 drive the seven segments A to G. Segments A to G are _shared_ by all four digits on the display. There is another, different set of pins that control which digit is currently active.  There is no way to turn on the display segments to show a `5` on the leftmost digit while simultaneously showing a `3` on the rightmost digit.

Instead, we drive the four digits on the display by continuously looping over the
digits one-by-one. The inner loop will display all four digits in quick succession. It turns on the leftmost digit, waits a short
length of time, and turns off that digit, then repeats the process for each of the other three digits. You might think that turning a
digit on and off would cause it to flicker. The key is to sequence through
the digits so fast that our eyes cannot see them changing. Good thing
computers are fast!

Implement the display refresh loop in `apps/clock.c`. Use the functions from the `timer` module to control the wait time. Loop though all
four digits, turning each on for 2500 microseconds. Do you see any flicker?

#### 6. Implement clock

In the basic assignment, the clock should display the minutes and
seconds that have elapsed since the clock program began executing.

The clock displays zero when the program
begins. The inner loop continually refreshes the 4-digit display, updating the value displayed to match the elapsed time. Make sure to test that the timer is calibrated correctly
so the clock is running at the right rate.

Note that the clock time is counting elapsed time since the clock program started, which is not quite the same value as the system tick count.  Clock time and the system tick count change at the same rate, but start at different values. Your program will need to implement this logic.

### Extension: Set Time
Remember to commit and push your basic submission, then create an extension branch with

    $ git checkout -b assign2-extension

Add two buttons to your clock breadboard and connect them to GPIO pins 2 and 3.
Build a user interface that allows you to set the time. You should be able to
set the minutes and seconds separately.  Strive for an interface design that is
easy to use and that works even after the clock starts running. It can be
challenging to build an interface with just a few buttons!

When reading button presses on the Pi, you will quickly realize that pressing
the button once may cause the value on the GPIO pin to change multiple times.
This is due to physical characteristics of the button mechanism which cause the
button circuit to open and close multiple times during a press.  To address
this issue, implement **debouncing** by checking whether the value change on
the GPIO pin corresponds to an actual button press or one of these
spurious events.  This can be done by checking that the GPIO pin reads the
button press value for a long enough time (that is, these spurious events will
change the GPIO value quickly, meaning if you check the value of the pin as
pressed, then wait a bit longer and see it as unpressed, that means it was a
spurious event). Experiment with the amount of time required to register a
valid press so that your buttons click easily without having to hold them down
too long, but do not generate extra button press events for a single physical
button press.

_Want to add another cool feature as an extension?_ Go for it!
Stopwatches, a better set time interface, personal messages, Larson-scanning
digits -- the sky is the limit.

In either case, be sure to document your changes/interface in a `README.md`
file committed to your repository so that your grader can test it out!

### Magic files <a name="magic"></a>

The starter project contains additional code files `start.s` and `cstart.c` and the file `memmap`. The map file is used by the linker when building the program and the two source files provide the minimum startup to set up a C program to run in the bare metal environment. A bit later in the course, we will study these files to understand how they work and why they are necessary. Feel free to look into the files now to get a sneak preview, but don't worry if you don't fully understand them yet. We will discuss them in more detail soon!

### Submit
Submit the finished version of your assignment by making a git "pull request",
following the steps given in the [Assignment 0 writeup](/assignments/assign0/).
Remember to make separate pull requests for your basic and extension
submissions.

For this assignment, we will be using an automated tester to test your gpio
library.  To promote the practice of fixing bugs in your code, you will be
granted the opportunity to fix bugs reported by the automated tester for a
partial refund (you can gain back up to half the points deducted).
Furthermore, fixing bugs in your code will put you in a better place to earn
the full system bonus at the end of the quarter (bonus points awarded for
submitting a working system using entirely your own code written for
assignments).

**The automated tester will deduct half a point for any warnings generated
when compiling your code**. Warnings are okay while your code is still in
active development (e.g.  prototyping/experimenting), but should be addressed
when your code is stable.  One method to ensure that you have no warnings
generated is to add the flag `-Werror` to the compile command in your Makefile.
This flag will cause a compiler error when a warning is generated, and can be
added before submission to ensure that no warnings sneak through.
