#include <stdint.h>
#include "std_string.h"
#include "std_io.h"
#include "std_cctype.h"
#include "vgap_io.c"
#include "idt.h"
/*

www.pentacom.jp/pentacom/bitfontmaker2
https://lvgl.io/tools/fontconverter

0x0000'7C00 : boot.asm
0x0000'7E00 : Cekirdek
0x000b'8000 : VGA-karakter
0x000A'0000 : VGA-piksel
0x0009'0000 : yigin

*/


void kernel_main(void) 
{                      
    idt_init();
    
    drawRectangle(20,20, 100, 50, VGA_Color_LIGHT_BLUE);
    print_string_at_vgap(50, 30,"abc", VGA_Color_CYAN);

    print_char_at_vgap(0,30, 'A', VGA_Color_YELLOW);


    while (1) 
    {
        __asm__("hlt");
    }
}