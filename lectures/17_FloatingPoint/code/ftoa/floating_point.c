#include "printf.h"
#include "ftoa.h"

void main() {
    char buf[256];
    float a = 12.7e6;
    ftoa(a,buf,10);
    printf("a: %s\n",buf);    
    
    double b = 0.0000000087654;
    ftoa(b,buf,20);
    printf("b: %s\n",buf);    
    
    double c = 1234567890.0987654321;
    ftoa(c,buf,20);
    printf("c: %s\n",buf);    
}
