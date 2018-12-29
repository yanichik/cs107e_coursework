// banner.c
// Prints a banner to the UART using the external keyboard
// and the font information

#include "font.h"
#include "printf.h"
#include "keyboard.h"

#define MAX_LINE 6

//#define DEBUG

void print_letter(int letter)
{
    int font_size = font_get_size();
    int font_width = font_get_width();
    unsigned char img[font_size];
    font_get_char(letter, img, sizeof(img));
    for (int i=0; i < font_size; i++) {
        printf("%c",img[i] == 0xff ? 'X' : ' ');
        if ((i+1) % font_width == 0) printf("\n");
    }
}

void extract_line_from_char(int letter, int line, char *buffer)
{
    int font_size = font_get_size();
    int font_width = font_get_width();
    unsigned char img[font_size];
    font_get_char(letter, img, sizeof(img));

    for (int i=line * font_width; i < line * font_width + font_width; i++) {
        *buffer++ = img[i] == 0xff ? 'X' : ' ';
    }
    *buffer = '\0';
}

void main(void)
{
    printf("Type (on the external keyboard!) a line of %d or fewer characters, then press return!\n",MAX_LINE);
    keyboard_init();
    while (1) {
        char letters[MAX_LINE];
        int line_index = 0;
        while (1) {
            char letter = keyboard_read_next();
            if (letter == '\n') break;
#ifndef DEBUG
            if (line_index > 0 && letter == '\b') {
                printf("\b \b");
                line_index--;
                continue;
            }
            if (line_index == MAX_LINE) continue;
            letters[line_index++] = letter;
            printf("%c",letter);
#else
            print_letter(letter);
#endif
        }
        printf("\n\n");
#ifdef DEBUG
        continue;
#endif

        int font_width = font_get_width();
        int font_height = font_get_height();

        for (int line_num = 0; line_num < font_height; line_num++) {
            char full_line[font_width * line_index];
            full_line[0] = '\0';
            for (int i=0; i < line_index; i++) {
                extract_line_from_char(letters[i],line_num,full_line + i * font_width);
            }
            printf("%s\n",full_line);
        }
    }
}

