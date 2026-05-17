[org 0x7C00]
bits 16

main:
    mov ah, 0x09        
    mov al, 'A'         ; karakter
    mov bh, 0x00        ; opengl back-front buffer gibi bisey anlamadim
    mov bl, 0x21        ; renk    
    mov cx, 10          ; adet miktari    
    int 0x10

    ;|---8bit--|-----8---------|     
    ;[Arka Plan][Karakter rengi]

    ;0x00 siyah
    ;0x01 mavi
    ;0x02 yesil
    ;0x04 kirmizi
    ;0x07 acik gri
    ;0x0A acik yesil
    ;0x0C acik kirmizi
    ;0x0F beyaz

jmp $

times 510-($-$$) db 0
dw 0xAA55