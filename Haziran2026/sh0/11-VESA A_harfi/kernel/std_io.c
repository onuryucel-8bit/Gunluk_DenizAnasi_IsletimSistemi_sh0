#include "std_io.h"

static int cursorPos = 0;

const int WINDOW_WIDTH = 80;
const int WINDOW_HEIGHT = 25;

int vgaIndex = 0;

static Color_t charBackgroundColor = Blue;
static Color_t charForegroundColor = White;

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

    //cursor low
    outb(VGA_REG_PORT, 0x0F);
    pos |= inb(VGA_DATA_PORT);

    //cursor high
    outb(VGA_REG_PORT, 0x0E);
    pos |= ((uint16_t)inb(VGA_DATA_PORT)) << 8;

    return pos;
}

//http://www.osdever.net/FreeVGA/vga/crtcreg.htm
void set_cursor(int x, int y)
{
	uint16_t pos = y * WINDOW_WIDTH + x;

    //select internal VGA register
	outb(VGA_REG_PORT, 0x0F);
    //read/write selected register
	outb(VGA_DATA_PORT, (uint8_t) (pos & 0xFF));
	outb(VGA_REG_PORT, 0x0E);
	outb(VGA_DATA_PORT, (uint8_t) ((pos >> 8) & 0xFF));
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(VGA_REG_PORT, 0x0A);
	outb(VGA_DATA_PORT, (inb(VGA_DATA_PORT) & 0xC0) | cursor_start);

	outb(VGA_REG_PORT, 0x0B);
	outb(VGA_DATA_PORT, (inb(VGA_DATA_PORT) & 0xE0) | cursor_end);
}

void disable_cursor()
{
	outb(VGA_REG_PORT, 0x0A);
	outb(VGA_DATA_PORT, 0x20);
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

void putchar_at(char ch, uint8_t x, uint8_t y)
{
    uint16_t index = y * WINDOW_WIDTH + x;
    video[index] = (charBackgroundColor << 12 | charForegroundColor << 8 | ch);
}

void print_string_at(const char* str, uint8_t x, uint8_t y)
{
    uint16_t index = y * WINDOW_WIDTH + x;

    while(*str != 0)
    {
        switch (*str)
        {

        //ENTER
        case ASCII_NEWLINE:
            index += WINDOW_WIDTH;
            index -= index % WINDOW_WIDTH;
            break;

        case ASCII_SPACE:
            video[index] = (charBackgroundColor << 12 | charForegroundColor << 8 | ' ');
            index++;
            break;        

        case ASCII_BACKSPACE:
            index -= 1;
            video[index] = (charBackgroundColor << 12 | charForegroundColor << 8 | ' ');
        break;

        case ASCII_TAB:
            index += 4;
        break;
        
        default:           
            video[index] = (charBackgroundColor << 12 | charForegroundColor << 8 | *str);
            index++;
            break;
        }

        if(index > WINDOW_WIDTH * WINDOW_HEIGHT)
        {
            index = 0;
        }

        str++;
    } 
}

void print_stringC(const char* str, Color_t bg, Color_t fg)
{
    Color_t oldBg = charBackgroundColor;
    Color_t oldFg = charForegroundColor;

    charBackgroundColor = bg;
    charForegroundColor = fg;

    print_string(str);

    charBackgroundColor = oldBg;
    charForegroundColor = oldFg;
}

void print_string(const char* str)
{
    while(*str != 0)
    {
        switch (*str)
        {

        //ENTER
        case ASCII_NEWLINE:
            vgaIndex += WINDOW_WIDTH;
            vgaIndex -= vgaIndex % WINDOW_WIDTH;
            break;

        case ASCII_SPACE:
            video[vgaIndex] = (charBackgroundColor << 12 | charForegroundColor << 8 | ' ');
            vgaIndex++;
            break;        

        case ASCII_BACKSPACE:
            vgaIndex -= 1;
            video[vgaIndex] = (charBackgroundColor << 12 | charForegroundColor << 8 | ' ');
        break;

        case ASCII_TAB:
            vgaIndex += 4;
        break;
        
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

void print_memory(uint32_t* adr, uint32_t size)
{
    
    char buffer[11];
       
    for (int i = 0; i < size; i++)
    {
        uint8_t* p = (uint8_t*)&adr[i];
        
        hex_to_str32((uint32_t)(adr + i), buffer);
        print_string(buffer);
        print_string(": ");

        for (int j = 0; j < 4; j++)
        {
            hex_to_str8(p[j], buffer);
            print_string(buffer);
            print_string(" ");
        }

        print_string("\n");
    }
    
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

void set_color(Color_t bg, Color_t fg)
{
    charBackgroundColor = bg;
    charForegroundColor = fg;
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

void hex_to_str8(uint8_t value, char* buffer)
{
    char hex[] = "0123456789ABCDEF";

    buffer[0] = '0';
    buffer[1] = 'x';

    buffer[2] = hex[(value >> 4) & 0xF];
    buffer[3] = hex[value & 0xF];

    buffer[4] = '\0';
}

void hex_to_str16(uint16_t value, char* buffer)
{
    char hex[] = "0123456789ABCDEF";

    buffer[0] = '0';
    buffer[1] = 'x';

    buffer[2] = hex[(value >> 12) & 0xF];
    buffer[3] = hex[(value >> 8) & 0xF];
    buffer[4] = hex[(value >> 4) & 0xF];
    buffer[5] = hex[value & 0xF];

    buffer[6] = '\0';
}

void hex_to_str32(uint32_t value, char* buffer)
{
    char hex[] = "0123456789ABCDEF";

    buffer[0] = '0';
    buffer[1] = 'x';

    buffer[2] = hex[(value >> 28) & 0xF];
    buffer[3] = hex[(value >> 24) & 0xF];
    buffer[4] = hex[(value >> 20) & 0xF];
    buffer[5] = hex[(value >> 16) & 0xF];

    buffer[6] = hex[(value >> 12) & 0xF];
    buffer[7] = hex[(value >> 8) & 0xF];
    buffer[8] = hex[(value >> 4) & 0xF];
    buffer[9] = hex[value & 0xF];

    buffer[10] = '\0';
}