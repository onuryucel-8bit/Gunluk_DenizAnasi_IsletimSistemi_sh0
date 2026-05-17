[org 0x7c00]
bits 16

main:
    call EnableA20

    cli

    ;gdt tablosunu yukle
    lgdt [gdt_descriptor]

    ;PM moda gec
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp codeseg:StartPM



EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
ret

%include "gdt.asm"

[bits 32]

StartPM:
    mov ax, dataseg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ecx, 0
    ;vga adresi
    mov ebx, 0xB8000
    .clearScreen:
        ;vga[ebx] = (uint16_t)(renk(uint8_t) | karakter(uint8_t))
        mov word [ebx], 0x1000
        ;ebx += 2 2bayt adresi kaydir
        add ebx, 2
        ;sayac i++
        add ecx, 1
        ;sayac < width*height
        cmp ecx, 2000 
        jne .clearScreen

    

    jmp $$

times 510-($-$$) db 0
dw 0xAA55