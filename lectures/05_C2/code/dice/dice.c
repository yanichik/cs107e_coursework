#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int nrolls = 0;

    srand(time(0));
    while (1) {
        int val = rand() % 6;
        if (val == 4) break;
        nrolls++;
    }
    printf("It took %d tries to roll a 4.\n", nrolls);
    return 0;
}
