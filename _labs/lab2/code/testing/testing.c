// File: testing.c
// ---------------
// Unit testing example

#include "assert.h"

// The is_odd function is intended to return a true/false value
// that reports whether its argument is odd. But oops-- the code as 
// written below is buggy!  Something this simple we could validate
// "by inspection" but we are going to use this as an opportunity
// to try out our support for simple unittests. The assert() function
// can be used to validate whether an expression returns the
// expected result. You assert a condition that must be true
// and if the expression evalutes to false, an error is raised.
// assert() uses the LEDs on the Pi as a simple status indication. 
// If an assert fails, it will stop executing the program
// and flash the red LED. If the program finishes executing and 
// no test was failed, it will turn on the green LED. 
// Thus if you end with the red LED of doom, you know your
// program is failing at least one test.

int is_odd(int n)
{
    return (n & 0x2) != 0;  // OOPS buggy!
}

void main(void) {
    assert(!is_odd(0));
    assert(is_odd(107));
    assert(is_odd(5));
    assert(!is_odd(4));
    assert(!is_odd(10));
	// read cstart.c to find out what happens after main() finishes
}
