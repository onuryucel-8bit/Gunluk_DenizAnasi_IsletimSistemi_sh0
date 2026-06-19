#include <stdint.h>
#include "std_string.h"
#include "std_io.h"
#include "std_cctype.h"
#include "idt.h"

/*

0x0000'7C00 : boot.asm
0x0000'7E00 : Cekirdek
0x000b'8000 : VGA
0x0009'0000 : yigin

*/

void kernel_main(void) 
{    
    
    clear_screen(Blue);

    set_color(Red, Green);
        
    print_string("TEST2\n");    
    
    set_cursor(vgaIndex,0);
    
    idt_init();
     
    uint32_t* a = (uint32_t*)0x7C00;
    
    print_memory(a, 5);

    set_color(Red, Blue);

    print_string_at("hmmmm", 40, 10);

    while (1) 
    {
        __asm__("hlt");
    }
}