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
0x0009'0000 : yigin ~15mb
0x00F0'0000 : heap

*/


void kernel_main(void) 
{                      
    idt_init();
    
    printf("Bazlama Yiyen Deniz Anasi!\n");
        
    uint8_t str[16];
        
    while (1)
    {        
        scanf(str, 16);
        
        if(!strcmp(str, "CLS"))
        {
            clearBuffer(VGA_Color_BLACK);
            vgay = 0;
            vgax = 0;
        }
        else
        {
            printf("ne diyon? ?_? bi halt anlamiyorum\n");
        }
    }
    
    

    while (1) 
    {        
        __asm__("hlt");
    }
}