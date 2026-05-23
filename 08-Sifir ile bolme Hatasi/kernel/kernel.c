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

    //print_string("TEST");
    //set_cursor(vgaIndex,0);
    //uint16_t pos = get_cursor_position();

    idt_init();

    //print_int(sizeof(idtr));

    //print_string("Kernel main()");
  
    volatile int a = 5;
    volatile int b = 0;

    a /= b;
 
    while (1) 
    {
        __asm__("hlt");
    }
}