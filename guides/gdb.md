---
layout: page
title: Guide to using GDB in simulation mode
---

The GDB debugger is a superb tool for observing and manipulating a
running program. Becoming facile with a full-featured debugger such as
`gdb` adds a critical superpower to your effectiveness as a software engineer. 

In our bare metal world, the options for debugging are more
limited than they would be in a hosted environment. We are not able to
monitor and interact with our program actually executing on the
Raspberry Pi. However, we can run `gdb`  on a local system in simulation mode. 
You can single-step through the program, set breakpoints, print variables, and
so on, all while the program is running on the simulator. Observing what 
is happening in the simulator can help you understand what your 
code is doing and help you find your bugs.

Be aware, though, that simulation is not the same as running
the real program. The simulator does not attempt to model 
the peripheral registers such as GPIO on the Raspberry Pi. For example,
consider the blink program that drives the GPIO registers to blink an LED
connected to the Pi's GPIO pins. If you run that same code in the
simulator, nothing happens. The simulator is not talking to your
Raspberry Pi (you won't even need it to be plugged in!), nor is it doing
anything special with the memory addresses in the GPIO range. 
There are definitely things you cannot debug in simulation mode!

For example, suppose we want to simulate the following
program to blink an LED on and off.

    .globl _start
    _start:

    // configure GPIO 20 for output
    ldr r0, =0x20200008
    mov r1, #1
    str r1, [r0]

    mov r1, #(1<<20)

    loop:

        // set GPIO 20 high
        ldr r0, =0x2020001C
        str r1, [r0]

        // delay
        mov r2, #0x3F0000
        wait1:
            subs r2, #1
            bne wait1

        // set GPIO 20 low
        ldr r0, =0x20200028
        str r1, [r0]

        // delay
        mov r2, #0x3F0000
        wait2:
            subs r2, #1
            bne wait2

    b loop

We compile the program using the ARM assembler. 
The option `-g` assembles the program with debugging information. 
The assembler will place symbol information 
and line numbers in the `.o` file so that `gdb` can use it.

    $ arm-none-eabi-as -g blink.s -o blink.o
    $ arm-none-eabi-gcc -nostdlib blink.o -o blink.elf

The `blink.elf` file is typically the penultimate step in our build, right 
before we extract the raw binary instructions into the `blink.bin` that is
sent to the Pi.  The `elf` version of the file is the one used by the gdb simulator.

We can now run `blink.elf` using the simulator in `gdb`.

    $ arm-none-eabi-gdb blink.elf
    GNU gdb (GDB) 7.8.1
    Copyright (C) 2014 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "--host=x86_64-apple-darwin14.0.0 --target=arm-none-eabi".
    Type "show configuration" for configuration details.
    For bug reporting instructions, please see:
    <http://www.gnu.org/software/gdb/bugs/>.
    Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.
    For help, type "help".
    Type "apropos word" to search for commands related to "word"...
    Reading symbols from blink.o...(no debugging symbols found)...done.
    (gdb)

The first thing we need to do is configure `gdb` to use the simulator.

    (gdb) target sim
    Connected to the simulator

Then load the program:

    (gdb) load
    Loading section .text, size 0x48 vma 0x8000
    Start address 0x8000
    Transfer rate: 576 bits in <1 sec.

`gdb` prints the size of the program (48 bytes) and
the start address (0x8000).

Let's set a breakpoint at `_start`:

    (gdb) break _start
    Breakpoint 1, _start () at blink.s:6

Note that `gdb` knows about the source file and line numbers.

    (gdb) list
    1	.globl _start
    2	_start:
    3	
    4	// configure GPIO 20 for output
    5	ldr r0, =0x20200008
    6	mov r1, #1
    7	str r1, [r0]
    8	
    9	mov r1, #(1<<20)
    10	

Now run it:

    (gdb) run
    Starting program: blink.elf
    Breakpoint 1, _start () at blink.s:6
    6   mov r1, #1

Note that we ran the first `ldr` instruction 
and the program stopped at line 6, the `mov` instruction.

Let's inspect all the register values

    (gdb) info registers
    r0             0x20200008 538968072
    r1             0x0 0
    r2             0x0 0
    r3             0x0 0
    r4             0x0 0
    r5             0x0 0
    r6             0x0 0
    r7             0x0 0
    r8             0x0 0
    r9             0x0 0
    r10            0x0 0
    r11            0x0 0
    r12            0x0 0
    sp             0x800 0x800
    lr             0x0 0
    pc             0x8004 0x8004 <_start+4>
    cpsr           0x13 19

or a single value register 0, `$r0`.

    (gdb) print/x $r0

Success, we loaded 0x20200008 into register 0!
`print/x` says to print in hexadecimal format.

Now let's step one instruction, and inspect the registers again.

    (gdb) stepi
    7   str r1, [r0]

Again, success. We loaded 1 into r1.
The next instruction to be executed is the store instruction.
Let's execute it.

    (gdb) stepi
    9   mov r1, #1

Let's *examine* (using the `x` command) memory at a given address
to see if it has the right contents.

    (gdb) x 0x20200008
    0x20200008: 0x00000001
    (gdb) x $r0
    0x20200008: 0x00000001

We have stored 1 at address 0x20200008. 

Continue debugging this program.
In particular, debug the delay loop.
What does CPSR stand for?
Inspect the values of CPSR as you step through the delay loop.
What value does CPSR have when `bne` returns to `wait1`?
What values does CPSR have when `bne` does not branch
and the loop is exited?

### Configuring your gdb setup

GDB can ask a lot of annoying questions and not recall previous commands
by default.  I put the following in a ".gdbinit" configuration file 
in my home directory to fix that:

	% cat ~/.gdbinit 
	set history expansion
	set confirm off

Whenever you start gdb, the commands from your ~/.gdbinit configuration 
file are read and executed. These defaults are useful in general for any
run of gdb.  

For a program that only is run in simulation mode, you might want to
avoid having to repeatedly set the target and load the program. For this, 
put a local .gdbinit configuration file in the project directory:

	% cat ./.gdbinit
	target sim
	load

Whenever you start gdb in this directory, the commands from this
.gdbinit file will set the the simulator target and load the program
automatically.

### Commands

Here is a list of useful `gdb` commands.

|Command|Abbrv|Description|
|:------|:---:|:----------|
|run|r|start program|
|quit|q|quit gdb|
|⬆️||scroll up through already executed commands (down-arrow goes down)|
|cont|c|continue execution after a break|
|break [where]|b [where]|set breakpoint, [where] can be function name/line number/address of instruction|
|delete [n]|d [n]|removes n'th breakpoint|
|delete|d|removes all breakpoints|
|info break|i b|lists all breakpoints|
|stepi|si|execute next assembly instruction|
|stepi [n]|si [n]|execute next n assembly instructions|
|nexti|ni|execute next assembly instruction, stepping over function calls|
|nexti [n]|ni [n]|execute next n assembly instructions, stepping over function calls|
|step|s|execute the next line of C source (can be multiple assembly instructions)|
|next|n|execute the next line of C source, stepping over function calls|
|where||show stack backtrace up to current execution|
|disas [addr]||disassemble instructions at given address|
|disas/r [addr]||same, adds hex machine code for instructions|
|info registers|i r|dump contents of all registers|
|print/d [expr]|p/d [expr]|print expression in decimal|
|print/x [expr]|p/x [expr]|print expression in hex|
|print/t [expr]|p/t [expr]|print expression in binary|
|x/HOW [addr]||Examine contents of memory in given format, HOW is 3 letters for repeatcount, format, size|
|display [expr]||automatically print the expression each time the program is halted|
|info display||show list of automatically displays|
|undisplay [n]||undisplay 1 remove an automatic display|
|help [cmdname]|h| get help for gdb command


### GDB Macros

Many programmers don't know about gdb macros, but they can be quite handy!  Suppose we
want to see which instructions in our code modify the cpsr register.
We can define a simple macro "np" to step a single instruction and print
the cpsr register in hex.

	(gdb) def np
	Type commands for definition of "n".
	End with a line saying just "end".
	>nexti
	>p/x $cpsr
	>end

Run it a bit:

	(gdb) b _start
	Breakpoint 1 at 0x8004: file blink.s, line 6.
	(gdb) r
	6 mov r1, #1
	(gdb) np
	7	str r1, [r0]
	$1 = 0x13
	...

The value of cpsr will be printed after each executed instruction.

### Tui mode

By default, gdb operates in plain-text mode with a single command
window. There is also a simple graphical mode, enabled with the `-tui`
option, that can split your window into various panes:

    $ arm-none-eabi-gdb -tui blink.elf

If I use the gdb command `layout asm` followed by `layout reg`, I get the following split window. 

<img title="Tui split-screen" src="../images/tui.png">

The upper pane displays current values for all registers, the middle pane is my assembly instructions, the bottom pane is my normal gdb command window. If I single-step with `si`, the register values will update automatically (those values that changed are highlighted) and middle pane will follow instruction control flow. This is a super-convenient view of what is happening at the machine level -- try it out!

To learn more about `tui` mode, check out this section in [an external GDB guide](https://beej.us/guide/bggdb/#regasm).

### More GDB resources
CS107 has a nice introduction in their [GDB guide](http://cs107.stanford.edu/guide/gdb.html).
Looking to learn some fancier tricks? See these articles Julie wrote for a 
programming journal: [Breakpoint Tricks](http://cs107.stanford.edu/resources/gdb_coredump1.pdf) 
and [gdb's Greatest Hits](http://cs107.stanford.edu/resources/gdb_coredump2.pdf). 
There's also the full online gdb manual to learn all the ins and outs: 
[http://sourceware.org/gdb/current/onlinedocs/gdb/index.html](http://sourceware.org/gdb/current/onlinedocs/gdb/index.html).


### Installing GDB

If you are on Linux and don't have the ARM GDB installed, you can use
this simple bash script (save it to a file, and run "bash <file>"):

	export TARGET=arm-none-eabi
	export PREFIX=$HOME/bin/$TARGET
	export PATH=$PATH:$PREFIX/bin
	export VERSION=7.8.1
	export GDB=gdb-$VERSION

	rm -rf $GDB

	# Get archives
	wget http://ftp.gnu.org/gnu/gdb/$GDB.tar.gz

	# Extract archives
	tar xzvf $GDB.tar.gz 

	mkdir build-gdb
	cd build-gdb
	../$GDB/configure --target=$TARGET --prefix=$PREFIX --enable-interwork --enable-multilib
	make 
	make install

GDB will now be in:

	%  ls ~/bin/arm-none-eabi/bin/
	arm-none-eabi-gdb*  arm-none-eabi-run*

Note that if you are missing packages this depends on, it can fail in mysterious ways.
My distribution was missing `makeinfo` and screen manipulation routines.
I am on Ubuntu, so a package install...

	sudo apt-get install texinfo
	sudo apt-get install libncurses5-dev

...fixed the problem.  There are guides for installing on Windows or Mac in the "guides" section.
