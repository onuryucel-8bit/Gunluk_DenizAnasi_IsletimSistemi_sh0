#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include "std_string.h"
#include "std_io.h"

//kesme adres bilgisi ve diger zamzingolar
typedef struct __attribute__((packed))
{
    uint16_t offset_lower;  //adres
    uint16_t selector;      //gdt code segment selector(kernel code segment)  
    uint8_t zero;           //Rezerv her zaman sifir, x86 islemci programcinin erisiminin olmadigi ic kisimda kullaniliyor galiba       
    uint8_t types_attr;     //Present bit | privilege level | gate type
    uint16_t offset_upper;  //adres
} IDT;

//kesme boyutu nerde baslayip bittigi hakkinda bilgi
typedef struct __attribute__((packed))
{
    uint16_t limit;
    uint32_t base;

}idtr;


void idt_init();
void idt_set(int intrerrupt_no, void* address);
void idt_zero_handler();

#endif