[bits 32]

global idt_load
global isr_divide_zero
global isr_keyboard
global isr_timer
global no_interrupt

extern idt_timer_handler
extern idt_zero_handler
extern idt_keyboard_handler
extern no_interrupt_handler

idt_load:
    push ebp
    mov ebp, esp
   
    mov ebx, [ebp + 8]
    lidt [ebx]
    sti

    pop ebp
ret

no_interrupt:
    cli
    pusha
    call no_interrupt_handler

    
    iretd

isr_keyboard:
    
    pusha

    call idt_keyboard_handler

    popa
    
    iretd

isr_divide_zero:
    cli

    pusha

    call idt_zero_handler
    
.hang:
    hlt
    jmp .hang

    ;popa

    ;iretd