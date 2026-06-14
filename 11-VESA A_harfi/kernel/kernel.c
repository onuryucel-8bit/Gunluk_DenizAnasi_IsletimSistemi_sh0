#include <stdint.h>
#include "std_string.h"
#include "std_io.h"
#include "std_cctype.h"
#include "idt.h"

/*

www.pentacom.jp/pentacom/bitfontmaker2
https://lvgl.io/tools/fontconverter

0x0000'7C00 : boot.asm
0x0000'7E00 : Cekirdek
0x000b'8000 : VGA
0x0009'0000 : yigin

*/



typedef struct  __attribute__ ((packed))
{
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];

}vbe_mode_info_structure;

vbe_mode_info_structure* vbe = (vbe_mode_info_structure*)0x500;


uint8_t charA [16] = 
{
	[0] = 0b11111111,
	[1] = 0b10000001,
	[2] = 0b10000001,
	[3] = 0b10000001,

	[4] = 0b11111111,
	[5] = 0b10000001,
	[6] = 0b10000001,
	[7] = 0b10000001,
};




void draw_pixel24b(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t* framebuffer = (uint8_t*)vbe->framebuffer;
	uint32_t index = y * vbe->pitch + x * (vbe->bpp / 8);

    framebuffer[index + 0] = r;
    framebuffer[index + 1] = g;
    framebuffer[index + 2] = b;
}

void draw_pixel32b(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
    if (x >= vbe->width || y >= vbe->height)
	{
        return;
	}

    uint32_t* framebuffer = (uint32_t*)vbe->framebuffer;

    uint32_t pitch = vbe->pitch / 4;   // convert bytes → pixels

    uint32_t index = y * pitch + x;

    framebuffer[index] =
        (r << 16) |
        (g << 8)  |
        b;
}

void kernel_main(void) 
{                      
    idt_init();
    
	
	
    for (size_t x = 0; x < 500; x++)
	{
    	draw_pixel24b(x, 100, 0, 255, 0);
	}
	

	

    while (1) 
    {
        __asm__("hlt");
    }
}