#include "idt.h"

IDT idt_desc[256];
idtr idtr_descriptor;

extern void idt_load(idtr* ptr);
extern void isr0();

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

void idt_init()
{
    //for idt_desc[i] = 0
    memset(idt_desc, 0, sizeof(idt_desc));


    idtr_descriptor.limit = sizeof(idt_desc) - 1;
    idtr_descriptor.base = (uint32_t)idt_desc;

    idt_set(0, isr0);

    idt_load(&idtr_descriptor);
}
