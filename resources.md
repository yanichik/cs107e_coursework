---
layout: page
title: Other resources
permalink: /resources/
toc: true
---

## Demos

* [Raspberry Pi GPIO Pinout](https://pinout.xyz/) website. Nice way to see alternate
  functions by clicking each pin. Also, click Ground and you see all the
  other Ground pins.

* An interactive demo of how the
[ARM assembler's immediate value encoder](https://alisdair.mcdiarmid.org/arm-immediate-value-encoding/#play-with-it) works.

* [VisUAL](http://salmanarif.bitbucket.io/visual/index.html)
emulates the ARM instruction set and allows you to step through an assembly program.
Pat used this tool in lecture.

  *Note that VisUAL uses a
  [slightly different ARM assembly syntax](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0773a/chr1383143764305.html)
  from the GNU syntax we use in the course -- for example, you don't
  put colons after labels in VisUAL.*

* Matt Godbolt's [Compiler Explorer](http://gcc.godbolt.org/) lets you
  quickly see how C source code maps to compiled assembly. (Be sure to
  choose the compiler "ARM gcc 4.8.2", which is close to what we use
  for the course. Check out the colorize option, too.)

* [cdecl.org](http://cdecl.org/) converts "C gibberish" to and from
English.

* [Repl](https://repl.it/languages/c) can run C code for you.
This can be handy when you need to test something brief or small!

* This virtual [Seven Segment Display](http://www.uize.com/examples/seven-segment-display.html)
will come in handy in a future lab. This demo teaches you to link bits to characters on a seven-segment-display.

* A [demonstration](http://pgbovine.net/rosetta/c-demo.html) of nifty pointer use to reverse a string.

## Informational Resources

### Raspberry Pi

We are using the Raspberry Pi A+ in class. The A+ is similar to the B+.

* [Raspberry Pi Board Schematics](https://github.com/raspberrypi/documentation/blob/master/hardware/raspberrypi/schematics/README.md)

### ARM architecture

The Raspberry Pi A+ uses a Broadcom BCM2835 chip. 
Inside the chip is an ARM1176JFZ-S processor 
which is based on the ARMv6 architecture.

* [Broadcom BCM2835 Peripherals Documentation](../readings/BCM2835-ARM-Peripherals.pdf )

  * [Errata](http://elinux.org/BCM2835_datasheet_errata)

  * [GPIO Pad Control](http://www.scribd.com/doc/101830961/GPIO-Pads-Control2).

* The ARM1176JFZ-S processor is documented in the 
[Technical Reference Manual](http://infocenter.arm.com/help/topic/com.arm.doc.ddi0301h/DDI0301H_arm1176jzfs_r0p7_trm.pdf).  

* ARM1176JFZ-S processors use the ARMv6 architecture,
which is documented in [ARMv6 Architecture Manual](../readings/armv6.pdf).
The following [excerpt](../readings/armisa.pdf)
describes just the instructions.


* ARM System-on-Chip Architecture (2nd Edition), Steve Furber.
Steve Furber was the principal design of the first ARM processor.
The diagrams of the ARM architecture are based on the diagrams
in Chapter 4: ARM Organization and Implementation.

* ARM System Developer's Guide: Designing and Optimizing System Software (The Morgan Kaufmann Series in Computer Architecture and Design), Andrew Sloss, Dominic Symes, and Chris Wright, 2004. This book is a bit dated, but still provides an excellent overview of low-level ARM programming.

* Excellent [slides](http://twins.ee.nctu.edu.tw/courses/ip_core_02/handout_pdf/Chapter_2.pdf) by Prof. Yen at NCTU on the ARM processor core and instruction sets.

### ARM Assembly Language

* Carl Burch's
  [Introduction to ARM Assembly Language](http://www.toves.org/books/arm/)
  is highly recommended starting point.

  *Like VisUAL above, Burch's introduction uses the
  [older ARM syntax](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0773a/chr1383143764305.html)
  instead of the GNU syntax we use.*

* [Worldwind Tour of ARM Assembly](http://www.coranac.com/tonc/text/asm.htm) from the TONC Guide to programming the Nintendo Game Boy Advance (which uses am ARM processor).

* [Davespace Introduction to ARM Course](http://www.davespace.co.uk/arm/introduction-to-arm/index.html).

* [Thinkingeek ARM Assembler for the Raspberry Pi](http://thinkingeek.com/2013/01/09/arm-assembler-raspberry-pi-chapter-1/).

### Bare Metal Programming

* David Welch's excellent set of [bare metal programming examples](https://github.com/dwelch67/raspberrypi).

* Steve Halliday's [videos](http://computersciencevideos.org/Raspberry-Pi/Raspberry-Pi-Setup) about programming the raspberry pi.

* Alex Chadwick's [Baking Pi Course](http://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/).

* The [Raspberry Pi Bare Metal Forum](http://www.raspberrypi.org/forums/viewforum.php?f=72) has lots of information from experienced developers. Venturing into the forum is a great way to learn advanced techniques. 

### C Programming Language

* [EssentialC](http://cslibrary.stanford.edu/101)

* *The C Programming Language, 2nd Ed.*, B. Kernighan and D. Ritchie.
A digital copy of K&R is available to Stanford students via 
[Safari Books Online](http://proquest.safaribooksonline.com.ezproxy.stanford.edu/book/programming/c/9780133086249).

* *The Definitive Guide to GCC, 2nd Ed.*, William von Hagen, Apress, 2006
[pdf](http://sensperiodit.files.wordpress.com/2011/04/hagen-the-definitive-guide-to-gcc-2e-apress-2006.pdf)
