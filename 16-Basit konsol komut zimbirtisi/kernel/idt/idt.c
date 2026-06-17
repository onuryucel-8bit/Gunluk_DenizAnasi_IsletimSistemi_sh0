#include "idt.h"
#include "idtKey.h"

IDT idt_desc[256];
idtr idtr_descriptor;

#define BUFFER_LIMIT 64
uint8_t buffer[BUFFER_LIMIT];
static uint8_t head = 0;
static bool f_lineReady = false;

extern void idt_load(idtr* ptr);
extern void isr_divide_zero();
extern void isr_keyboard();
extern void isr_timer();
extern void no_interrupt();

void no_interrupt_handler()
{
    //print_string("AAA!\n");
    outb(PIC_MASTER, EOI);
}

void idt_timer_handler()
{       
    //posx++;
    //print_char_at_vgap(posx - 1, 0, ' ', VGA_Color_BLACK);
    //print_char_at_vgap(posx, 0, 'A', VGA_Color_GREEN);
    outb(PIC_MASTER, EOI);
}

void idt_keyboard_handler()
{
    f_lineReady = false;
    uint8_t scancode = inb(KEYBOARD_PORT);
    uint8_t key = scancode & 0x7F;

    if(scancode_names[key])
    {
        if(scancode & 0x80)
        {            
            //const char* ch = scancode_names[key];
            //print_char(*ch, VGA_Color_BLUE);

            buffer[head] = (uint8_t)*scancode_names[key];

            putchar(buffer[head]);
            
            if(buffer[head] == '\n')
            {                
                f_lineReady = true;
            }

            head++;
            if(head == BUFFER_LIMIT)
            {
                head = 0;
            }            
        }
    }
    
    outb(PIC_MASTER, EOI);
}

void idt_zero_handler()
{
    //print_string("HATA:: Sifir ile bolunme hatasi islemci durdu...");
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
    outb(PIC_MASTER, INIT_COMMAND_WORD);
    outb(PIC_SLAVE, INIT_COMMAND_WORD);

    outb(PIC_MASTER_DATA, 0x20); // master offset = 32
    outb(PIC_SLAVE_DATA, 0x28);  // slave offset = 40
    
    outb(PIC_MASTER_DATA, 0x04); //Efendi PIC'i kole ile bagliyoruz
    outb(PIC_SLAVE_DATA, 0x02);  //Kole PIC'i kirbac ile IRQ2 pinine bagliyoruz

    outb(PIC_MASTER_DATA, ICW1_ICW4);
    outb(PIC_SLAVE_DATA, ICW1_ICW4);

    outb(PIC_MASTER_DATA, PIC_UNMASK_ALL);
    outb(PIC_SLAVE_DATA, PIC_UNMASK_ALL);
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
    //outb(0x21, 0xFD); // enable only keyboard (IRQ1)
    //outb(0xA1, 0xFF); // disable slave IRQs

    idt_set(0, isr_divide_zero);    

    idt_set(0x20, isr_timer);
    idt_set(0x21, isr_keyboard);

    
    idt_load(&idtr_descriptor);
}

uint8_t getChar()
{
    while(head == 0)
    {
        __asm__("hlt");
    }
    
    head--;
    return buffer[0];
}

void scanf(char* str, uint16_t size)
{    
    while(!f_lineReady)
    {        
        __asm__("hlt");        
    }
           
    uint16_t i = 0;
    while (i < size - 1 && buffer[i] != '\n')
    {
        str[i] = buffer[i];
        i++;
    }
    
    str[i] = '\0';
    
    f_lineReady = false;
    buffer[head] = 0;
    head = 0;
}
