org 0x7C00
bits 16

;CR: Carriage Return
%define KEY_ENTER 0x0D

main:
    
    mov si, buffer
    call read

    
    mov si, buffer
    call print

    jmp main

jmp $

%include "io.asm"

;10 bayt yer ayriliyor
buffer: times 10 db 0
;10 bayt yer ayriliyor
sayi2: times 10 db 0


times 510-($-$$) db 0
dw 0xAA55