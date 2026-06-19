#ifndef STD_IO_H
#define STD_IO_H

#include <stdint.h>

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

#define ASCII_ENTER   0x0D  
#define ASCII_NEWLINE 0x0A  //'\n'


extern int vgaIndex;

#define VGA_ADRES 0xb8000

extern Color_t charBackgroundColor;
extern Color_t charForegroundColor;
extern uint16_t* video;

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t get_cursorPosition();
void set_cursor(int x, int y);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();
uint16_t get_cursor_position();
void putchar(char ch);
void print_string(const char* str);
void print_int(uint32_t value);
void clear_screen(Color_t color);

void intToStr(int N, char* str);
void hex_to_str(uint8_t value, char* buffer);

#endif