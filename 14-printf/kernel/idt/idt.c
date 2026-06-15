#include "idt.h"

IDT idt_desc[256];
idtr idtr_descriptor;

uint8_t buffer[64];
static uint8_t head = 0;
//static uint8_t tail = 0;

const char* scancode_names[256] =
{
    [0x01] = "ESC",
    [0x02] = "1",
    [0x03] = "2",
    [0x04] = "3",
    [0x05] = "4",
    [0x06] = "5",
    [0x07] = "6",
    [0x08] = "7",
    [0x09] = "8",
    [0x0A] = "9",
    [0x0B] = "0",
    [0x0C] = "-",
    [0x0D] = "=",
    [0x0E] = "\b",  //BACKSPACE
    [0x0F] = "\t",  //TAB

    [0x10] = "Q",
    [0x11] = "W",
    [0x12] = "E",
    [0x13] = "R",
    [0x14] = "T",
    [0x15] = "Y",
    [0x16] = "U",
    [0x17] = "I",
    [0x18] = "O",
    [0x19] = "P",
    [0x1A] = "[",
    [0x1B] = "]",

    [0x1C] = "\n",
    [0x1D] = "LCTRL",

    [0x1E] = "A",
    [0x1F] = "S",
    [0x20] = "D",
    [0x21] = "F",
    [0x22] = "G",
    [0x23] = "H",
    [0x24] = "J",
    [0x25] = "K",
    [0x26] = "L",
    [0x27] = ";",
    [0x28] = "'",
    [0x29] = "`",

    [0x2A] = "LSHIFT",
    [0x2B] = "\\",

    [0x2C] = "Z",
    [0x2D] = "X",
    [0x2E] = "C",
    [0x2F] = "V",
    [0x30] = "B",
    [0x31] = "N",
    [0x32] = "M",
    [0x33] = ",",
    [0x34] = ".",
    [0x35] = "/",

    [0x36] = "RSHIFT",
    [0x37] = "KP_*",
    [0x38] = "LALT",
    [0x39] = " ",   //SPACE-bosluk
    [0x3A] = "CAPSLOCK",

    [0x3B] = "F1",
    [0x3C] = "F2",
    [0x3D] = "F3",
    [0x3E] = "F4",
    [0x3F] = "F5",
    [0x40] = "F6",
    [0x41] = "F7",
    [0x42] = "F8",
    [0x43] = "F9",
    [0x44] = "F10",

    [0x45] = "NUMLOCK",
    [0x46] = "SCROLLLOCK",

    [0x47] = "KP_7",
    [0x48] = "KP_8",
    [0x49] = "KP_9",
    [0x4A] = "KP_-",
    [0x4B] = "KP_4",
    [0x4C] = "KP_5",
    [0x4D] = "KP_6",
    [0x4E] = "KP_+",
    [0x4F] = "KP_1",

    [0x50] = "KP_2",
    [0x51] = "KP_3",
    [0x52] = "KP_0",
    [0x53] = "KP_.",

    [0x57] = "F11",
    [0x58] = "F12"
};


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
    uint8_t scancode = inb(KEYBOARD_PORT);
    uint8_t key = scancode & 0x7F;

    if(scancode_names[key])
    {
        if(scancode & 0x80)
        {            
            //const char* ch = scancode_names[key];
            //print_char(*ch, VGA_Color_BLUE);

            buffer[head] = (uint8_t)*scancode_names[key];
            head++;
            if(head == 8)
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
    while(*buffer != ASCII_KEY_ENTER)
    {        
        __asm__("hlt");
    }
            
    uint16_t i = 0;
    while (i < size - 1 && buffer[i] != ASCII_KEY_ENTER)
    {
        str[i] = buffer[i];
        i++;
    }

    str[i] = '\0';
}
