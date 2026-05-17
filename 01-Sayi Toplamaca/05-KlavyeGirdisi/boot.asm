org 0x7C00
bits 16

main:

    mov ah,0x0
    int 0x16    
    ;Return:
    ;AH = BIOS scan code
    ;AL = ASCII character
    
    call printChar
    jmp main


jmp $


;al => ekrana yazilacak karakter
printChar:    
    mov ah, 0x0e            
    int 0x10
ret



times 510-($-$$) db 0
dw 0xAA55