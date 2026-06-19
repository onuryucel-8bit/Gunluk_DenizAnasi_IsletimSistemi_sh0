/*
24.05.2026

Tuslara basildiginda 

idt.c
void idt_keyboard_handler()
{
    hex_to_str(inb(0x60), buffer);
    print_string(buffer);
    print_string("\n");
   
    outb(0x20, 0x20);
}

durum + Tus bilgisi ekrana yazilmakta

*/



#include <stdint.h>
#include "std_string.h"
#include "std_io.h"
#include "std_cctype.h"
#include "idt.h"



void kernel_main(void) 
{    
    
    clear_screen(Blue);
        
    charBackgroundColor = Black;
    charForegroundColor = White;

   
    print_string("TEST2\n");
    print_string("TEST2\n");
    print_string("TEST2\n");
    
    set_cursor(vgaIndex,0);
    //uint16_t pos = get_cursor_position();

    idt_init();
    
    //print_int(sizeof(idtr));

    //print_string("Kernel main()");
  
    //volatile int a = 5;
    //volatile int b = 0;

    //a /= b;
 
    while (1) 
    {
        __asm__("hlt");
    }
}