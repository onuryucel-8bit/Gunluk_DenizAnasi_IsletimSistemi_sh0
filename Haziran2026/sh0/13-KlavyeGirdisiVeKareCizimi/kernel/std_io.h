//registers
//http://www.osdever.net/FreeVGA/vga/graphreg.htm


#ifndef STD_IO_H
#define STD_IO_H

#include <stdint.h>

#define VGA_REG_PORT   0x3D4
#define VGA_DATA_PORT  0x3D5

//https://wiki.osdev.org/VGA_Hardware
//wiki.osdev.org/Printing_To_Screen
typedef enum 
{
    Black,
    Blue,	
    Green,	
    Cyan,	
    Red,   
    Magenta,
    Brown,	
    Gray,	
    DarkGray,
    LightBlue,	
    LightGreen,	
    LightCyan,	
    LightRed,
    LightMagenta,
    Yellow,
    White,  
}Color_t;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

#define ASCII_NEWLINE   0x0A  // '\n'
#define ASCII_SPACE     0x20  // ' '
#define ASCII_BACKSPACE 0x08  // <=
#define ASCII_TAB       0x09  // '\t'


extern int vgaIndex;

#define VGA_ADRES 0xb8000

extern uint16_t* video;

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

//================================================//
//----------------cursor--------------------------//
//================================================//
void set_cursor(int x, int y);
uint16_t get_cursorPosition();
uint16_t get_cursor_position();
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();
//================================================//
//================================================//
//================================================//

void set_color(Color_t bg, Color_t fg);

void print_memory(uint32_t* adr, uint32_t size);

void putchar(char ch);
void putchar_at(char ch, uint8_t x, uint8_t y);

void print_stringC(const char* str, Color_t bg, Color_t fg);
void print_string(const char* str);
void print_string_at(const char* str, uint8_t x, uint8_t y);
void print_int(uint32_t value);

void clear_screen(Color_t color);

void intToStr(int N, char* str);
void hex_to_str8(uint8_t value, char* buffer);
void hex_to_str16(uint16_t value, char* buffer);
void hex_to_str32(uint32_t value, char* buffer);

#endif