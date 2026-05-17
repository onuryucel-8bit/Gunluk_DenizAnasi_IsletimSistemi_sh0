[org 0x7C00]
bits 16

main:
    mov ah, 0x0e
    ;ekrana yazilacak karakter
    mov al, 'A'    
    int 0x10

jmp $

times 510-($-$$) db 0
dw 0xAA55