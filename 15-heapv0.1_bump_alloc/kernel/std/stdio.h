#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#include "../std/stdlib.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 200

extern const uint8_t font8[128][8];

typedef enum
{
    VGA_Color_BLACK         = 0,
    VGA_Color_BLUE          = 1,
    VGA_Color_GREEN         = 2,
    VGA_Color_CYAN          = 3,
    VGA_Color_RED           = 4,
    VGA_Color_MAGENTA       = 5,
    VGA_Color_BROWN         = 6,
    VGA_Color_LIGHT_GREY    = 7,
    VGA_Color_DARK_GREY     = 8,
    VGA_Color_LIGHT_BLUE    = 9,
    VGA_Color_LIGHT_GREEN   = 10,
    VGA_Color_LIGHT_CYAN    = 11,
    VGA_Color_LIGHT_RED     = 12,
    VGA_Color_LIGHT_MAGENTA = 13,
    VGA_Color_YELLOW        = 14,
    VGA_Color_WHITE         = 15

}VGAColor;


extern uint8_t* vga;
extern uint16_t vgax, vgay;

//=======================================================//
//=======================================================//
//=======================================================//

void drawPixel(uint16_t x, uint16_t y, VGAColor color);
void clearBuffer(VGAColor color);
void drawFilledRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, VGAColor color);
//DDA algo
void drawline(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, VGAColor color);
void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, VGAColor color);

/*
             (x, y).---------.(x + width, y)
                   |         |
                   |         |
                   |         |
                   |         |
    (x, y + height).---------.(x + width, y + height)
*/
void drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, VGAColor color);

void setConsoleColor(VGAColor color);
void setbgColor(VGAColor color);

//=======================================================//
//=======================================================//
//=======================================================//

void print_char(uint8_t ch);
void print_char_at_vgap(uint16_t x, uint16_t y, uint8_t ch);
void print_string_vgap(const char* str);
void print_string_at_vgap(uint16_t x, uint16_t y, const char* str);

void intToStr(int N, char* str);

void print_int(uint32_t value);
void print_int_at(uint16_t x, uint16_t y, uint32_t value);
void print_hex(uint32_t dec);

void putchar(char ch);
void printf(const char* fmt, ...);

#endif