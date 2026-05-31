#include "std_io.h"

static int cursorPos = 0;

const int WINDOW_WIDTH = 80;
const int WINDOW_HEIGHT = 25;

int vgaIndex = 0;

Color_t charBackgroundColor = Blue;
Color_t charForegroundColor = White;

uint16_t* video = (uint16_t*)VGA_ADRES;

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
	uint16_t pos = y * WINDOW_WIDTH + x;

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

        case ASCII_NEWLINE:
            vgaIndex += WINDOW_WIDTH;
            vgaIndex -= vgaIndex % WINDOW_WIDTH;
            break;

        /*case ASCII_ENTER:
            vgaIndex -= vgaIndex % WINDOW_WIDTH;
            break;
        */
        default:           
            video[vgaIndex] = (charBackgroundColor << 12 | charForegroundColor << 8 | *str);
            vgaIndex++;
            break;
        }

        if(vgaIndex > WINDOW_WIDTH * WINDOW_HEIGHT)
        {
            vgaIndex = 0;
        }

        str++;
    } 
}

void print_int(uint32_t value)
{
    /*
    45 0x0000'002D
    */

    char str[32];
    intToStr(value, str);

    print_string(str);
    
}

void clear_screen(Color_t color)
{
    //[arka][on][karakter]
    //[4]   [4] [8]
    color = color << 4;

    for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) 
    {
        video[i] = (uint16_t)(' ' | (color << 8));
    }
}


//https://www.geeksforgeeks.org/c/how-to-convert-an-integer-to-a-string-in-c/
void intToStr(int N, char* str) 
{
    int i = 0;
  
    // Save the copy of the number for sign
    int sign = N;

    // If the number is negative, make it positive
    if (N < 0)
        N = -N;

    // Extract digits from the number and add them to the
    // string
    while (N > 0) 
    {      
        // Convert integer digit to character and store
      	// it in the str
        str[i++] = N % 10 + '0';
      	N /= 10;
    } 

    // If the number was negative, add a minus sign to the
    // string
    if (sign < 0) 
    {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
    for (int j = 0, k = i - 1; j < k; j++, k--) 
    {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

void hex_to_str(uint8_t value, char* buffer)
{
    char hex[] = "0123456789ABCDEF";

    buffer[0] = '0';
    buffer[1] = 'x';

    buffer[2] = hex[(value >> 4) & 0xF];
    buffer[3] = hex[value & 0xF];

    buffer[4] = '\0';
}