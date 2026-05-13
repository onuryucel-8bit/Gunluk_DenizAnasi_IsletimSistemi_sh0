org 0x7C00
bits 16

;CR: Carriage Return
%define KEY_ENTER 0x0D
;'\n'
%define NEWLINE 0x0A

main:
    
    mov si, buffer
    call read
    
    mov si, buffer
    call print

    ;jmp main

    mov si, buffer
    mov di, sayi2
    mov cx, 10
    call strcpy

    mov al, NEWLINE
    call printChar

    mov al, KEY_ENTER
    call printChar

    mov si, buffer
    call print
jmp $

%include "io.asm"
%include "string.asm"

;10 bayt yer ayriliyor
buffer: times 10 db 0
;10 bayt yer ayriliyor
sayi2: times 10 db 0


times 510-($-$$) db 0
dw 0xAA55