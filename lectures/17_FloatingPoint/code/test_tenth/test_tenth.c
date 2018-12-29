#include "printf.h"
#include "ftoa.h"

void main() {
    char buf[256];
    float f = 0.1;
    // convert to a string, with 20 decimal places of precision
    ftoa(f,buf,20);
    printf("f: %s\n",buf);    
}
