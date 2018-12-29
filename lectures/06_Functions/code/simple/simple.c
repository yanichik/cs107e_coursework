#include "assert.h"

int sum(int n, int m)
{
    return n + m;
}

int abs(int v)
{
    return v < 0 ? -v : v;
}

int min(int x, int y)
{
    return x < y ? x : y;
}

int delta(int a, int b)
{
    return abs(a - b);
}

void main(void)
{
    int p = 33, q = 107;
    assert(sum(p, q) == (min(p, q) + delta(p, q)));
}
