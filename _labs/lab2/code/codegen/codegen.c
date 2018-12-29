// File: codegen.c
// ---------------
// C examples that demo some interesting properties/transformations
// when C compiler generates ARM instructions.

// Note: each function begins with a goofy statement that 
// initializes a variable to a value read from memory.
// If instead we had init to a constant, gcc is so smart that
// it will optimize away the rest of the work, so this
// is here to trick the compiler to treat as "random" value



// Part (a): arithmetic
// Study each of the C statements and the translation to ARM assembly
// line 1: ARM has no negate instruction -- what is used instead?
// line 2: What is used in place of multiply for this expression?
// line 3: Note that some parts of the complex arithmetic expression 
// is pre-computed by the compiler, and other parts are not. 
// Why the difference?  Change the initialization of num to
// a constant value, e.g. int num = 3. Now how much of the
// expression is the compiler able to precompute?
int part_a(void)
{
    int num = *(int *)100;

    num = -num;
    num = 5 * num;
    num =  (num & ~(-1 << 4)) * (((12*18 - 1)/2) + num); 
    return num;
}

// Part (b): if/else
// An if/else can be implemented in assembly as two distinct code 
// paths and a control flow that routes to one path or the other 
// using branch. Alternatively, it could be expressed as one combined 
// sequence of conditionally executed instructions.
// First, review the generated assembly when compiled with flag -Og
// (lightly optimized). Now change flag -Og to -O1 (more optimized)
// and review how the generated assembly changes.
// Count the instructions in the two versions and you'll see 
// there are 6 executed for -Og (if either branch is taken) and the
// same for -O1. Can you come up with a theory to explain the
// performance advantage of the -O1 version despite executing the
// same number of instructions?
int part_b(void)
{
    int num = *(int *)100;

    if (num < 0) {
        num++;
    } else {
        num--;
    }  
    return num;
} 

// Part (c): loops
// This function is a C version of the delay loop we used in
// the blink program.  When using flag -Og or -O1,
// the compiler's generated assembly is a close match to our
// hand-written assembly. But if you notch it up to -O2
// (aggressive optimization), the generated assembly is
// significantly different. Why? What can you change in the
// C code to prevent that undesired transformation?
void part_c(void)
{
    int delay = 0x3f00;
    while (--delay != 0) ;
}

// Part (d): pointers
// The function below accesses memory using pointer/array
// notation. The code is divided into pairs of statements
// which perform a similar operation, but have subtle differences 
// (such as adding a typecast, or operating on pointer of 
// different pointee type). How do those differences affect
// the generated assembly? 
int part_d(void)
{
    int *ptr = 0;
    char *cptr = 0;
    int n = *ptr;

    *ptr = 23;      // compare to next ine
    *(char *)ptr = 23;

    ptr[10] = 15;   // compare to next line
    cptr[10] = 15;

    n = *(ptr + n); // compare to next line
    n = ptr[n];

    return n;
}


void main(void)
{
    // make calls to each function so none eliminated as dead code/unreachable
    part_a();
    part_b();
    part_c();
    part_d();
}

