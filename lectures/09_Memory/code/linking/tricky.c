#include "tricky.h"

// initialized variables
int x = 1;
const int x_const = 2;
static int x_static = 3;
static const int x_static_const = 4;

// uninitialized variables (equal to 0)
int y;
const int y_const;
static int y_static;
static const int y_static_const;

void tricky(int dx, int dy)
{
   x_static = x + x_static_const;
   x = x_const + dx;

   y_static = y + y_static_const;
   y = y_const + dy;

}
