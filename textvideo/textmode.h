#ifndef TEXTMODE_H
#define TEXTMODE_H

#include<stddef.h>
#include<stdint.h>


#define VGA_WIDTH 80
#define VGA_HEIGHT 24

enum vga_color
{
        COLOR_BLACK = 0,
        COLOR_BLUE = 1,
        COLOR_GREEN = 2,
        COLOR_CYAN = 3,
        COLOR_RED = 4,
        COLOR_MAGENTA = 5,
        COLOR_BROWN = 6,
        COLOR_LIGHT_GREY = 7,
        COLOR_DARK_GREY = 8,
        COLOR_LIGHT_BLUE = 9,
        COLOR_LIGHT_GREEN = 10,
        COLOR_LIGHT_CYAN = 11,
        COLOR_LIGHT_RED = 12,
        COLOR_LIGHT_MAGENTA = 13,
        COLOR_LIGHT_BROWN = 14,
        COLOR_WHITE = 15,
};

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

uint8_t color(enum vga_color bg,enum vga_color fg);
uint16_t vga_entry(char c, uint8_t col);
size_t strlen(const char* str);
void terminal_initialize();
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void clrscr();
void terminal_writestring(const char* data);
void terminal_putint(uint32_t i);


#endif

