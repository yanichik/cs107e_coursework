// This program waits until a button is pressed (GPIO 10)
// and turns on GPIO 20, then waits until the button is 
//released and turns off GPI0 20

volatile unsigned int * const FSEL1 = (unsigned int *)0x20200004;
volatile unsigned int * const FSEL2 = (unsigned int *)0x20200008;
volatile unsigned int * const SET0  = (unsigned int *)0x2020001C;
volatile unsigned int * const CLR0  = (unsigned int *)0x20200028;
volatile unsigned int * const LEV0  = (unsigned int *)0x20200034;


void main(void)
{    
    *FSEL1 = 0; // configure GPIO 10 as input
    *FSEL2 = 1; // configure GPIO 20 as output

    while (1) {

        // wait until GPIO 10 is low (button press)
        while ((*LEV0 & (1 << 10)) != 0) ;

        // set GPIO 20 high
        *SET0 = 1 << 20;

        // wait until GPIO 10 is high (button release)
        while ((*LEV0 & (1 << 10)) == 0) ;

        // clear GPIO 20
        *CLR0 = 1 << 20;
    }
}
