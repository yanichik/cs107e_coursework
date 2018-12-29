unsigned int *FSEL2 =  (unsigned int *)0x20200008;
unsigned int *SET0  =  (unsigned int *)0x2020001c;
unsigned int *CLR0  =  (unsigned int *)0x20200028;

#define DELAY 0x3f0000

void main(void)
{
   *FSEL2 = 1;

   while (1) {
        *SET0 = 1 << 20;
        for (int c = DELAY; c != 0; c--) ;
        *CLR0 = 1 << 20;
        for (int c = DELAY; c != 0; c--) ;
   }
}

