[org 0x7C00]
bits 16

main:

    mov si, message
    call print
jmp $

;si => str konumu
print:
    .print_Loop:    
        lodsb
        cmp al, 0
        je .done

        call printChar
        jmp .print_Loop
.done
ret

;al => ekrana yazilacak karakter
printChar:    
    mov ah, 0x0e            
    int 0x10
ret

message: db "DENIZ ANASI", 0

times 510-($-$$) db 0
dw 0xAA55