#include <stdint.h>

const int WIDTH = 80;
const int HEIGHT = 25;
#define VGA_ADRES 0xb8000
static int cursorPos = 0;
uint16_t* video = (uint16_t*)VGA_ADRES;

int vgaIndex = 0;

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

//[arka][on][karakter]
//[4]   [4] [8]
void putchar(char ch)
{
    video[vgaIndex] = (charBackgroundColor << 12 | charForegroundColor << 8 | ch);
    vgaIndex++;    
}

void print_string(const char* str)
{
    while(*str != 0)
    {
        video[vgaIndex] = (charBackgroundColor << 12 | charForegroundColor << 8 | *str);

        vgaIndex++;
        *str++;
    }
}

void kernel_main(void) 
{    
    //[arka][on]
    //[4][4]
    uint16_t attr = DarkGray << 4;
    

    for (int i = 0; i < WIDTH * HEIGHT; i++) 
    {
        video[i] = (uint16_t)(' ' | (attr << 8));
    }

    charBackgroundColor = Black;
    charForegroundColor = White;

    print_string("DENIZ ANASI");
    

    while (1) 
    {
        __asm__("hlt");
    }
}