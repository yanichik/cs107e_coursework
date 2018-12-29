unsigned int * const FSEL2 =  (unsigned int *)0x20200008;
unsigned int * const SET0  =  (unsigned int *)0x2020001c;
unsigned int * const CLR0  =  (unsigned int *)0x20200028;

void main(void)
{
   *FSEL2 = 1;

   while (1) {
        *SET0 = 1 << 20;
        for (int c = 0x3f0000; c != 0; c--) ;
        *CLR0 = 1 << 20;
        for (int c = 0x3f0000; c != 0; c--) ;
   }
}
