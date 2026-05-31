#include "idt.h"

IDT idt_desc[256];
idtr idtr_descriptor;

uint8_t buffer[5];

extern void idt_load(idtr* ptr);
extern void isr_divide_zero();
extern void isr_keyboard();
extern void isr_timer();
extern void no_interrupt();

void no_interrupt_handler()
{
    //print_string("AAA!\n");
    outb(0x20, 0x20);
}

void idt_timer_handler()
{   
    outb(0x20, 0x20);
}

void idt_keyboard_handler()
{
    hex_to_str(inb(0x60), buffer);
    print_string(buffer);
    print_string("\n");
   
    outb(0x20, 0x20);
}

void idt_zero_handler()
{
    print_string("HATA:: Sifir ile bolunme hatasi islemci durdu...");
}

void idt_set(int intrerrupt_no, void* address)
{
    IDT* desc = &idt_desc[intrerrupt_no];

    desc->offset_lower = (uint32_t)address & 0xffff;
    desc->selector = 0x08;
    desc->zero = 0;
    desc->types_attr = 0x8e;
    desc->offset_upper = (uint32_t)address >> 16;

    
}

void pic_remap()
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20); // master offset = 32
    outb(0xA1, 0x28); // slave offset = 40

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void idt_init()
{
    //for idt_desc[i] = 0
    memset(idt_desc, 0, sizeof(idt_desc));


    idtr_descriptor.limit = sizeof(idt_desc) - 1;
    idtr_descriptor.base = (uint32_t)idt_desc;
        
    for (size_t i = 0; i < TOTAL_INTERRUPTS; i++)
    {
        idt_set(i, no_interrupt);
    }

    pic_remap();
    outb(0x21, 0xFD); // enable only keyboard (IRQ1)
    outb(0xA1, 0xFF); // disable slave IRQs

    idt_set(0, isr_divide_zero);    
    idt_set(0x21, isr_keyboard);

    
    idt_load(&idtr_descriptor);
}
