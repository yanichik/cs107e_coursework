#include "printf.h"
#include "ftoa.h"

void main() {
    double a = 0.1;
    double b = 0.2;
    double c = 0.3;
    
    printf("0.1 + 0.2 == 0.3 ? %s\n", a + b == c ? "true" : "false");
}
