#include <stdint.h>
#include "std/string.h"
#include "std/stdlib.h"
#include "std/stdio.h"
#include "idt/idt.h"
#include "pong.h"
/*

0x0000'7C00 : boot.asm
0x0000'7E00 : Cekirdek
0x000b'8000 : VGA-karakter
0x000A'0000 : VGA-piksel
0x0009'0000 : yigin ~15mb
0x00F0'0000 : heap

*/

#define DEBUG_SERIAL_PORT

#ifdef DEBUG_SERIAL_PORT

#define PORT_COM1 0x3f8          // COM1

    #define DEBUG_init() init_serial()

    #define DEBUG_printChar(ch) write_serial(ch)
    #define DEBUG_printStr(str) write_serialStr(str)

    int init_serial() 
    {
        outb(PORT_COM1 + 1, 0x00);    // Disable all interrupts
        outb(PORT_COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
        outb(PORT_COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
        outb(PORT_COM1 + 1, 0x00);    //                  (hi byte)
        outb(PORT_COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
        outb(PORT_COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
        outb(PORT_COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
        outb(PORT_COM1 + 4, 0x1E);    // Set in loopback mode, test the serial chip
        outb(PORT_COM1 + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

        // Check if serial is faulty (i.e: not same byte as sent)
        if(inb(PORT_COM1 + 0) != 0xAE) 
        {
                return 1;
        }

        // If serial is not faulty set it in normal operation mode
        // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
        outb(PORT_COM1 + 4, 0x0F);

        return 0;
    }
    
    int is_transmit_empty() 
    {
        return inb(PORT_COM1 + 5) & 0x20;
    }

    void write_serial(char a) 
    {
        while (is_transmit_empty() == 0);

        outb(PORT_COM1,a);
    }

    void write_serialStr(const char* str)
    {
        while (*str)
        {
            write_serial(*str++);                        
        }   
    }
#else
    #define DEBUG_init() ((void)0)

    #define DEBUG_printChar(ch) ((void)0)
    #define DEBUG_printStr(str) ((void)0)

#endif


void consoleCLS()
{
    clearBuffer(VGA_Color_BLACK);
    vgay = 0;
    vgax = 0;
}

void getStackPointer()
{
    uint32_t esp;

    __asm__ volatile (
        "mov %%esp, %0"
        : "=r"(esp)
    );

    printf("esp = %x\n", esp);
}

void kernel_main(void) 
{                      
    idt_init();
        
    DEBUG_init();
    
    DEBUG_printStr("Konsol hmmmmm");

    printf("Bazlama Yiyen Deniz Anasi!\n");
    while(1)
    {
        Event_t event;

        while(pollEvent(&event))
        {
            if(event.pressed)
            {
                putchar(event.key);
            }
        }         
    }


   /*    
    uint8_t str[16];
        
    while (1)
    {        
        scanf(str, 16);
        
        if(!strcmp(str, "CLS"))
        {
           consoleCLS();
        }
        else if(!strcmp(str, "PONG"))
        {
            consoleCLS();
            

            pongRun();
        }
        else
        {
            printf("ne diyon? ?_? bi halt anlamiyorum\n");
        }
    }
    
    */

    while (1) 
    {        
        __asm__("hlt");
    }
}