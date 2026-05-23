#include <stdint.h>
#include "std_io.c"

void kernel_main(void) 
{    
    
    clear_screen(Blue);
    

    charBackgroundColor = Black;
    charForegroundColor = White;

    print_string("ABCDEF");
    set_cursor(vgaIndex,0);
    uint16_t pos = get_cursor_position();


    while (1) 
    {
        __asm__("hlt");
    }
}