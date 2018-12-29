#include "malloc.h"
#include "printf.h"
#include "strings.h"
#include "uart.h"

static void swap(char **p, char **q)
{
    char *tmp = *p;
    *p = *q;
    *q = tmp;
}

static void sort(char *arr[], int n)
{
    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i; j < n; j++) {
            if (strcmp(arr[j], arr[min]) < 0) min = j;
        }
        swap(&arr[i], &arr[min]);
    }
}

static int get_and_echo(void)
{        
    char ch = uart_getchar();
    if (ch == '\r') ch = '\n';
    uart_putchar(ch);
    return ch;
}

static void read_line(char buf[], int buflen)
{
    int n = 0;
    while (n < buflen - 1) {
        char ch = get_and_echo();
        if (ch == '\n') break;
        buf[n++] = ch;
    }
    buf[n] = '\0';
}


#define MAXLEN 128

void main(void)
{
    uart_init();

    int n = 0;
    char *names[MAXLEN];

    printf("Enter names, one per line.\n");
    while (n < MAXLEN) {
        char *line = malloc(MAXLEN);
        read_line(line, MAXLEN);
        if (strcmp(line, "") == 0) break;
        names[n++] = line;
    }

    printf("Read %d names.\n\nNow in sorted order:\n", n);
    sort(names, n);
    for (int i = 0; i < n; i++)
        printf("%s\n", names[i]);
}






