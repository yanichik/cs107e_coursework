---
layout: page
title: 'Assignment 4: Backtrace and Malloc'
permalink: /assignments/assign4/
released: true
toc: true
---

*Written by Julie Zelenski and Omar Rizwan*

**Due: Wednesdaay, October 31, 2018 at 11:30 AM**

## Goals
For this week's assignment, you'll again be playing the role of
library implementer to add a debugging aid (`backtrace.c`)
and a simple heap allocator (`malloc.c`) to your growing
collection of foundational routines.

After you finish this assignment, you will:

- be able to dissect the runtime stack in an executing program,

- further understand C data structures and memory layout,

- have leveled up your skills wrangling pointers in C, and

- appreciate the complexity and tradeoffs in implementing a heap allocator.

## Get started
Navigate to your copy of the `cs107e.github.io` repository and do a `git pull` to be sure you have the latest files from the courseware repo.

As in the last assignment, your `assign4-basic` branch has been created for you. Navigate to your `assignments` directory and check out the new branch.

```
$ cd cs107e_home/assignments
$ git fetch origin
$ git checkout assign4-basic
```

Consult the `Makefile` for more information on reusing code from previous
assignments. If you do this, you should double check that the latest copies of
your `gpio.c`, `timer.c`, `strings.c`, and `printf.c` are present in the
starter code.  If they are out of date, there are a couple possible reason why.
If you submitted a regrade pull request for assignment 2, you'll need to merge
the changes from the regrade branch into your `assign4-basic` branch with `git
merge assign2-regrade`.  Another case is if you pushed to an assign3 branch
after assign4 was released. In this case, you can merge your later changes with
`git merge assign3-basic`.  If your files are out of date and you don't fall
into one of these categories, contact a staff member to get help. 

The starter files for this assignment contain the modules `backtrace.c` and
`malloc.c` (with a few bits of starter code) and the application programs
`apps/heap.c` and `tests/test_heap.c` which are used to exercise the functions in the modules.

## Basic section

### Backtrace module
First, you'll implement the `backtrace` module, which provides functions to gather a backtrace and print it.

For example, imagine a program whose `main` function calls `print_triangle`, which then calls `printf`. A backtrace starting at `printf` might look something like this: 
```
#0 0x8250 at printf+60
#1 0x80d0 at print_triangle+128
#2 0x8118 at main+24
#3 0x8160 at _cstart+48
```
A backtrace is a listing of the current frames on the stack. The list begins with current function and traces the sequence of calls that led to this function. The backtrace ends at `_cstart`, which is the first function entered at program start.

The [backtrace.h](https://github.com/cs107e/cs107e.github.io/blob/master/cs107e/include/backtrace.h) header file declares these three functions and documents how the functions operate:

   - `backtrace`
   - `print_frames`
   - `print_backtrace`

We give you the code for the two print functions pre-written, so your job is to implement the `backtrace` function, which harvests stack frames. This is a small but mighty function. Completing it will definitely solidify your understanding the stack layout!

#### An example backtrace
We will refer to the 
[stack diagram](https://cs107e.github.io/labs/lab3/images/stack_abs.html)
from the first exercise of [lab 3](/labs/lab3) as our
example stack for backtrace. You may want to have the diagram open in another tab or have a printed version to annotate when going through this example.

A backtrace is represented as an array with `frame_t` elements, one struct for each function on the stack. Review
[`backtrace.h`](https://github.com/cs107e/cs107e.github.io/blob/master/cs107e/include/backtrace.h) 
to see the type definition of the struct `frame_t` and read the comments which explain the intent of the fields `resume_addr` and `resume_offset`.

You will harvest the information to fill in each `struct` by digging the frame information out of the runtime. 

The current value of the `fp` register is the "anchor" you need to start examining the stack. You must drop down to assembly to access a register. GCC has a handy convenience keyword to allow you to embed assembly into
your C code. The code sample below demonstrates how to retrieves the value of `fp` and store into a variable named `cur_fp`:

   ```
   void *cur_fp;
   __asm__("mov %0, fp" : "=r" (cur_fp));
   ```

(If you're 
   curious to learn more, check out the manual: [gcc support for inline assembly](https://gcc.gnu.org/onlinedocs/gcc/Using-Assembly-Language-with-C.html).)

Have the [stack diagram](https://cs107e.github.io/labs/lab3/images/stack_abs.html) open while you work through the following questions to reaffirm your understanding before starting. The currently executing function is `abs()` and the value of the `fp` register is `0x7ffffc4`. Consider the task of determining the `resume_addr` and `resume_offset` for the caller function `diff`.

   - If the executing function is `abs()` and you have the current value of
the `fp` register, where in the stack can you read the `resume_addr` for `diff`?

- How can you work from the `fp` for `abs()` to access the saved fp of its caller, the `diff` function?  How does the saved `fp` grant you access to the stack frame for `diff`? How do you then go from `diff`'s frame to the frame of the `main` function? What is the indication that you have hit the outermost stack frame where the backtrace should stop?

- The `resume_offset` is calculated by subtracting the address of the first instruction in the caller function from the resume address. What can you use in the stack frame for `diff` to locate the first instruction of a function? (Hint: may help to re-visit the first question on the 
[lab3 check-in](/labs/lab3/checkin) 
for a little bit of foreshadowing about this calculation.)

The final task in harvesting the backtrace is to get the function name.
There is a compiler option intended to support developers (such as yourself)
writing debugging tools that is a nice help here. If you compile with the flag `-mpoke-function-name`,
`GCC` will embed each function's name into the text section, at a
location preceding the function's first instruction!
Below is an excerpt from the gcc documentation
about this option.

_Note: below we have corrected a few details that are mis-identified in the official manual, 
so please use this version rather than refer back to the original._

   > `-mpoke-function-name`
   >
   > Write the name of each function into the text section, directly
   > preceding the function prologue. The generated code is similar to
   > this:
   >
   > ```
   > t0
   >     .ascii "arm_poke_function_name", 0
   >     .align
   > t1
   >     .word 0xff000000 + (t1 - t0)
   > arm_poke_function_name
   >     mov     ip, sp
   >     stmfd   sp!, {fp, ip, lr, pc}
   >     sub     fp, ip, #4
   > ```
   >
   > When performing a stack backtrace, code can inspect the value of
   > `pc` stored at `fp + 0`. If the trace function then looks at location
   > `pc - 16` and the top 8 bits are set, then we know that there is a
   > function name embedded immediately preceding this location and has
   > length `((pc[-4]) & ~0xff000000)`.

   How cool! Look at the assign4 `Makefile` and see that we've added
   `-mpoke-function-name` to the `CFLAGS`.

If the word preceding a function's first instruction has `0xff` in its upper byte, this is the signal that the function's name is stored there. You can then read the length off the lower 3 bytes and use the length to back up to the start of the string. Wacky! If you don't find the magic `0xff` in the right place, this indicates the function name is not available, in which case, use `"???"` as the name.

If we take the same example we've been working through and recompile with the
`-mpoke-function-name` flag, we get this  [memory diagram updated with embedded function names](images/diagram_with_poke.html). The stack frames are basically the same, but the instructions in the text section have been slightly rearranged to accommodate the function 
names that have been inserted. Look in the diagram and work out at what address you can access the string name for the `main` function as an example.

Note that the function name string is null-terminated and the terminator is
counted in the length. The use of 
`.align` causes the length of the name to be rounded up to a 
multiple of 4; additional null characters are used as padding. 
Thus, a function named `binky` will have its name embedded 
as `binky\0\0\0` and length of 8. Given that the name is
stored with its null terminator, you can access the string in-place and directly
store its address into the name field of a `frame_t` without making a copy of it.

Put all these steps together and you can create a function to harvest a backtrace from the current stack contents. This requires a surprisingly short piece of code, but it is dense with pointer arithmetic and typecasts, so go slow, and diagram out your steps carefully. Validating your backtrace against what is printed by `gdb`'s `backtrace` command can be a useful debugging technique.

### Malloc module
The global and local variables we have been using thus far serve the
needs of many programs, but more sophisticated applications necessitate
dynamic allocation. Dynamic allocation offers the programmer explicit,
direct control over sizing and lifetime of storage, but this
power comes with the responsibility to carefully allocate and
deallocate that memory. Using dynamic memory correctly and safely is a
challenge for the client; implementing a heap allocator correctly
and efficiently is a challenge for the implementer.

The [malloc.h](https://github.com/cs107e/cs107e.github.io/blob/master/cs107e/include/malloc.h) module declares three functions:

   - `malloc`
   - `free`
   - `realloc`

The starter code provides a sample heap allocator 
implementation in `malloc.c`. This
"bump allocator" is simple and correct, but fairly naive. 
It is provided only to serve as a reference point 
from which your own
heap allocator will be able to show substantial improvements.
 
The job of the heap allocator is reserve a large chunk of memory and then parcel it out to service allocation requests. The critical requirement for a heap allocator is to correctly service any combination of well-formed requests. Because `malloc` is so heavily-used, it is desirable that it be efficient in terms of space (recycling freed memory, compactly storing blocks) and time (quickly servicing operations). We'll put some effort toward recycling, but more aggressive performance efforts are not our focus for the assignment.


#### Step-by-step

1. **Study starter code.**

    Start by reviewing the [malloc.h](https://github.com/cs107e/cs107e.github.io/blob/master/cs107e/include/malloc.h) header file and the given code for the bump allocator in the file `malloc.c`.

    Make sure you understand what every line in the starter code is
doing. Your allocator will be significantly more complicated, so you
must start from a solid foundation. Here are some self-test questions to work through to verify your understanding:

    - How does the heap initializes itself on first use?
    - Where is the heap located in memory? How big is it?
    - Why does the code cast pointers to `char *` before doing pointer arithmetic?
    - If you request a 5-byte allocation, how much is actually allocated by the bump allocator?
    - Why can't the bump allocator free a previous allocation?
    - How is the realloc operation supposed to work? Now look to see how realloc is implemented in the bump allocator. Be sure to understand how and why this code works.


2. **Review background material on block headers.**

    Your implementation will add a header to each block 
    that tracks the block size and status (in-use or free). 
    Review these [block header diagrams](images/block_hdr)
    to understand the basic layout of a heap using block headers.

3. **Initialize the heap to one giant free block.**

    The initialization of the heap needs to be triggered at the first call to `malloc()`. 

    Assume that you have a total heap size of 16MB at your disposal. This free block will initially contain the entirety of the heap.

4. **Implement `malloc()` to service a request by splitting from the free block.**

    Each `malloc()` will split from the free block, by dividing it into
    two blocks, each with its own header. One block is portioned to the
    requested size, while the remainder is left in the free
    block. Subsequent requests will further split off the free block.

5. **Implement `free()` to update status in block header.**

    `free()` should access the block's header and mark it as free. 
    This doesn't yet recycle a free block, but marking it as free is the
    first step toward that.

6. **Implement `heap_dump()` to print out debugging information about your heap.**

    `heap_dump()` should walk your heap and print out information about each
    block such as its size and status. You can then call this function
    as-needed to get a visual representation on the contents of your heap.
    Write a test that allocates a few blocks in the heap and then calls
    `heap_dump()`. You should visually inspect the information printed out by
    your debugging function to validate that the layout and contents of the
    heap are what you expect.  When printing out information about each block,
    we recommend against printing out the full contents of the block (that is,
    printing out the value of each byte) as this will be difficult to work with
    when you start working with larger heaps.

7. **Upgrade `malloc()` to search freed blocks for reuse.**
   
    Rather than grab straight from the large free block,
    malloc should now instead walk the heap from beginning to end,
    examining each block header in hopes of finding a free block of an appropriate size that
    can be recycled.

    To advance through the blocks in the heap, read the size from the
    block's header and use the size in conjunction with pointer arithmetic to
    move from one block header to the next. Searching the heap for free
    blocks in this way is traversing an _implicit free list_ and taking
    the first free block large enough to service the request is known
    as _first fit_.

8. **Upgrade `free()` to coalesce adjacent free blocks.**
   
    Reusing single freed blocks is a good improvement, but it doesn't entirely solve the general recycling need. What happens if the client repeatedly allocates 8-byte blocks until the heap is full, frees all of them, then tries to allocate a 32-byte block? The heap contains way more than 32 bytes of free space, but it has been fragmented it into individual 8-byte blocks. We need a way to join those smaller blocks to service larger requests.

    Modify `free()` so that it examines the neighbor block after the newly freed
    block. If that forward neighbor is also free, then _coalesce_ the two
    blocks into one big free block. Then look at the forward neighbor of
    that bigger block and see if it's free in turn. Continue
    forward-coalescing until no further coalescing is possible.

10. **Upgrade `realloc()` to operate in-place when possible.**

    The last feature to add is to make `realloc` a bit smarter. The version of `realloc` given in the starter code always moves the payload data to a new location in the heap. It would be much more efficient if we could instead resize the block in place. This won't always be possible, but if the neighboring space is free and can be tacked on to the current block, we can save ourselves a lot of effort.  Modify `realloc()` to seize the opportunity to resize the block in-place and only move the block when it must.


You have summited Heap Allocator Mountain and earned your heap allocator merit badge-- **Congratulations!** Now go celebrate with some chocolate, a Dish hike, 
or a nice nap in the sun.

#### Malloc specification

All pointers returned by `malloc()` should be aligned to 8 bytes, the word size on our system. The most convenient way to follow the alignment rule is
to simply round up all requested sizes to a total block size (payload
plus header) that is a multiple of 8, and lay out blocks end to end. *The assignment originally
said 4 bytes, if you round to 4 that is OK. But you might encounter bugs if you store double or
long long (64-bit) values in dynamically allocated memory.*

The `man` page for `malloc()` can be used 
find out how to deal (or not deal) with edge cases -- what if
`malloc()` cannot fulfill a request, because it doesn't have a large
enough contiguous free block?  What if a caller runs `free()` on some
random pointer that it didn't actually get from `malloc()`? 

There are a few valid, but odd, uses that require making a special case. The four I know to watch out for are `malloc(0)`, `realloc(NULL, size)`,  `realloc(ptr, 0)` and `free(NULL)`. Read the man page to learn what the expected behavior is for each and follow along with the specification.


 <a name="testing"></a>
## Testing

The `apps/heap.c` program contains sample client code taken from labs 3 and 4 that uses `backtrace` and `malloc`. Use this program unchanged as a basic sanity test of your modules.

The `tests/test_heap.c` program is your file to do with what you wish. The starter code provides some example tests to get you started. You should augment and rework the test program to fit your needs.Remember that we allocate a point of the assignment grade for submitting your original test cases.  Think about ways to test the robustness of your heap. Does it function properly when the heap is full? Does it recycle freed blocks? Can you repeatedly allocate and free blocks of varying sizes?

## Extension
For this assignment, we have a set of possible extensions. You are welcome to
implement more than one of the options, but you will only receive points for a
single extension submission.

### Red Zone Allocator & Validator

What happens if a client allocates memory of a certain size and then mistakenly writes outside of the bounds?  The erroneous write not only stomps on the neighboring payload data, it is almost certain to destroy the critical heap housekeeping that is stored adjacent to the payload data. Many sad consequences will follow. 

Correctly managing dynamic memory can be tricky. Memory errors are all too common and can be very difficult to track down. Debugging tools such as [Valgrind](http://valgrind.org) are invaluable weapons against these insidious memory errors. For the extension, you are going to implement a "mini-Valgrind" that can help with tracking down these errors.

One technique for debugging memory errors uses _red zones_ around each payload. Each time you service a malloc request, you oversize the request by an extra 8 bytes. Place the actual payload in the middle with one 4-byte red zone before it and another 4-byte red zone after it. Write a distinctive value to the red zones. (Our implementation uses `0x107e107e`, though you are free to use [any distinctive non-offensive values you like](https://en.wikipedia.org/wiki/Hexspeak).)

Your backtrace module provides context to identify blocks. Modify your block header structure to add an array of three `frame_t` and fill it with a snapshot of the backtrace at the time of allocation.  Now when a block is found to be in error, you will be able to provide the mini-backtrace of where it was allocated from.

Modify `free` to verify that the contents of red zones are intact for the block currently being freed. If not, print an error report as shown below that identifies the block in error:

```
Address 0x00009bd0 has damaged red zone(s): [457e107e] [107e107e]
Block of size 5 bytes, allocated by
#0 0x89c8 at malloc+176
#1 0x8400 at heap_redzones+88
#2 0x845c at main+36
```

Our automated checker for this extension will expect an error message that
exactly matches the above format, with different values for the red zones,
block size, and backtrace depending on the test.

### Performance Tuning
For this extension option, you will tune your malloc implementation to achieve
a throughput of at least 50,000 requests per second.  To start, you should use
your timer module to measure the length of time required to service a certain
number of requests.  Make sure your performance evaluations allocate blocks of
varying sizes and alternate between allocating and freeing blocks to ensure
that your throughput is consistent with your implementation of coalescing and
recycling.

The biggest throughput sink of a heap allocator is the search to find an
appropriately-sized free block. The first fit approach scans the heap from
start to end, examining every block in the heap, both free and in-use. As the
heap gets more full, this technique degrades into quadratic-time: after `n`
allocations, a subsequent allocation will need to walk past all of the `n`
previous allocations to reach a free block.

There is a simple optimization that can help a lot here. Instead of always
searching from the start of the heap, make each subsequent search pick up where
the previous search left off. In this way, you avoid repeatedly re-scanning
long sequences of in-use blocks. This strategy is called "next fit".

To implement next fit, you can maintain a pointer to the most recently
allocated block and use it to start the search for a new block to allocate.
However, this will require you to update your search algorithm to properly wrap
around the heap and search until reaching the starting point.  Also, be sure to
consider edge cases such as when the most recently allocated block is coalesced
by `free()`.

### Buddy (Power of 2) Allocator
As mentioned in lecture, there are many popular strategies for implementing
`malloc`, each with varying trade-offs between performance and utilization.
While the coalescing algorithm implemented in the basic portion of this
assignment is advantageous in terms of utilization, it introduces overhead in
calls to `free()`.

The *buddy allocator* attempts to balance the utilization benefits of coalescing
with better runtime performance by using a fixed scheme for splitting and
merging blocks.  The strategy is to repeatedly split blocks in half, creating
two smaller "buddies" until a finding a block that is less than twice the size
of the requested allocation. 

For example, if we started with a 128 KB block and requested a 28 KB
allocation, the 128 KB block would be split into two 64 KB blocks, one of the
64 KB blocks would be split into two 32 KB blocks, and then the allocator would
return one of the 32 KB blocks.  Notice that the algorithm splits blocks until
it finds a block that is the size of the allocation rounded up to the nearest
power of two (because we started with a block size that was a power of two).
In practice, a buddy allocator will use a minimum block size to service small
requests, such as 64KB (so any request less than 32 KB will still be serviced
by a 64KB block).

One advantage of the buddy allocator's block splitting scheme is that
coalescing is simple (fast): when a block is freed, check if its "buddy" is
free, if so, coalesce. This happens recursively, so a coalesced block is
coalesced with its "buddy" if possible.  Another advantage is that the
coalescing operation can use a clever bit operation with the block's size and
address to efficiently determine the address of "buddy".

## Submission and automated checks
Submit the finished version of your assignment by making a git “pull request”.
Remember that you should not change the directory/file organization of the
starter code. Your submission should make edits to the existing files.

The automated checks here, as always, make sure that we can run your C
code and test and grade it properly, including swapping your tests for
ours.

CI will automatically check that:

- `apps/heap.c` is unchanged

- `make` completes successfully

- `make tests/test_heap.bin` completes successfully using your `tests/test_heap.c`

- `make tests/test_heap.bin` completes successfully using the original `tests/test_heap.c` from
  the starter code (we will swap this in before running it)

Again, if the automated test fails on your final submission, we will
automatically deduct 1 point from your basic grade.  Also remember
that we will deduct half a point for any compiler warnings that are
generated when compiling your code.

## Heap alligator
We close with this lovely picture from Jane Lange, talented CS107e alum and section leader.
![Heap alligator!](images/heapalligator.png)
