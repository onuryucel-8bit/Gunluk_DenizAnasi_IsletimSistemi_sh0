#include <stdint.h>
#include "std/string.h"
#include "std/stdlib.h"
#include "std/stdio.h"
#include "idt/idt.h"
/*

0x0000'7C00 : boot.asm
0x0000'7E00 : Cekirdek
0x000b'8000 : VGA-karakter
0x000A'0000 : VGA-piksel
0x0009'0000 : yigin

*/


void kernel_main(void) 
{                      
    idt_init();
    
    //print_char('A');

    drawFilledRectangle(20,20, 100, 50, VGA_Color_LIGHT_BLUE);    
    print_string_at_vgap(50, 30,"abc");

    printf("hmmm\nPrintf %d %d", 10, 200);


    while (1) 
    {        
        __asm__("hlt");
    }
}