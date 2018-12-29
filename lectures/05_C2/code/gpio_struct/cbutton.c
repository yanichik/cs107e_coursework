// This program waits until a button is pressed (GPIO 10)
// and turns on GPIO 20, then waits until the button is 
//released and turns off GPI0 20

// This struct is declared to exactly match the 
// layout of the gpio registers in memory
struct gpio {
    unsigned int fsel[6];
    unsigned int reservedA;
    unsigned int set[2];
    unsigned int reservedB;
    unsigned int clr[2];
    unsigned int reservedC;
    unsigned int lev[2];
};

volatile struct gpio * const gpio = (struct gpio *)0x20200000;


void main(void)
{    
    gpio->fsel[1] = 0; // configure GPIO 10 as input
    gpio->fsel[2]  = 1; // configure GPIO 20 as output

    while (1) {

        // wait until GPIO 10 is low (button press)
        while ((gpio->lev[0] & (1 << 10)) != 0) ;

        // set GPIO 20 high
        gpio->set[0]  = 1 << 20;

        // wait until GPIO 10 is high (button release)
        while ((gpio->lev[0]  & (1 << 10)) == 0) ;

        // clear GPIO 20
        gpio->clr[0] = 1 << 20;
    }
}
