struct rec {
    int i;
    int j;
    int a[2];
    int *p;
};

struct withchar {
    int i;
    int j;
    char a;
    char b;
    int k;
};

void main(void)
{
    struct rec r;
    r.i = 1;
    r.j = 2;
    r.a[0] = 3;
    r.a[1] = 4;
    r.p = (int *)0x8000;

    struct withchar wc;
    wc.i = 1;
    wc.j = 2;
    wc.a = 'a';
    wc.b = 'b';
    wc.k = 3;

    char arr[1024];
    for (int i=0; i < 1024 / 4; i++) {
        *((int *)arr + i) = 0xdeadbeef; // fill with deadbeef 
    }
    char *randomLocation = &arr[64];
    ((struct rec *)randomLocation)->i = 5;
    ((struct rec *)randomLocation)->j = 6;
    ((struct rec *)randomLocation)->a[0] = 7;
    ((struct rec *)randomLocation)->a[1] = 8;
    ((struct rec *)randomLocation)->p = (int *)0x8000;

}






