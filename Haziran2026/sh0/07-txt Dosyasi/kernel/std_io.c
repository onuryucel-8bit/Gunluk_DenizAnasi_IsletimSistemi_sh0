#include <stdint.h>

const int WIDTH = 80;
const int HEIGHT = 25;
#define VGA_ADRES 0xb8000
#define VGA_WIDTH 80
static int cursorPos = 0;
uint16_t* video = (uint16_t*)VGA_ADRES;

int vgaIndex = 0;

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


Color_t charBackgroundColor;
Color_t charForegroundColor;
//https://wiki.osdev.org/Inline_Assembly/Examples
//https://wiki.osdev.org/Port_IO
void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"(value), "Nd"(port)
    );
}

uint8_t inb(uint16_t port)
{
    uint8_t retvalue;

    __asm__ volatile (
        "inb %1, %0"
        : "=a"(retvalue)
        : "Nd"(port)
    );

    return retvalue;
}

uint16_t get_cursorPosition()
{
    uint16_t pos = 0;

    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);

    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;

    return pos;
}

//http://www.osdever.net/FreeVGA/vga/crtcreg.htm
void set_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

    //select internal VGA register
	outb(0x3D4, 0x0F);
    //read/write selected register
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

uint16_t get_cursor_position(void)
{
    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    return pos;
}


/*
Bit 76543210
    ||||||||
    |||||^^^-fore color
    ||||^----fore color bright bit
    |^^^-----back color
    ^--------back color bright bit OR enables blinking Text
*/
//[blink]       [background] [foreground] [char]
//[yanıp sönme] [arka]       [on]         [karakter]
//[1]           [3!]         [4]          [8]
void putchar(char ch)
{
    video[vgaIndex] = (charBackgroundColor << 12 | charForegroundColor << 8 | ch);
    vgaIndex++;    
}

void print_string(const char* str)
{
    while(*str != 0)
    {
        switch (*str)
        {
        case 10:
            vgaIndex += VGA_WIDTH;
            break;
        case 13:
            vgaIndex -= vgaIndex % VGA_WIDTH;
            break;
        default:           
            video[vgaIndex] = (charBackgroundColor << 12 | charForegroundColor << 8 | *str);
            vgaIndex++;
            break;
        }


        *str++;
    }
}

void clear_screen(Color_t color)
{
    //[arka][on][karakter]
    //[4]   [4] [8]
    color = color << 4;

    for (int i = 0; i < WIDTH * HEIGHT; i++) 
    {
        video[i] = (uint16_t)(' ' | (color << 8));
    }
}
