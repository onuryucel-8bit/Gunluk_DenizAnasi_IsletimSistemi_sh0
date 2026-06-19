[bits 32]

global idt_load
global isr0

extern idt_zero_handler

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8]
    lidt [ebx]
    ;sti

    pop ebp
ret

isr0:
    cli

    pusha

    call idt_zero_handler
    
.hang:
    hlt
    jmp .hang

    ;popa

    ;iretd