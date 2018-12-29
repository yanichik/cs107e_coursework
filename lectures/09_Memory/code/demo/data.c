#include "timer.h"

// uninitialized global and static
int gNum;
static int sgNum;

// initialized global and static
int iNum = 1;
static int siNum = 2;

// initialized global and static const
const int cNum = 3;
static const int scNum = 4;

int binky(void)
{
    siNum++;
    sgNum--;
    return siNum + sgNum + scNum;
}

int main(void)
{
    return timer_get_ticks() + binky();
}