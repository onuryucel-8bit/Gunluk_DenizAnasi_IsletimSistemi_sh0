;GIRDI
;SI <= girdinin tutulacagi adres
read:    

    .readStr_loop:

        call readChar
        ;karakter ?= KEY_ENTER
        cmp al, KEY_ENTER
        ;eger enter tusuna basildiysa donguyu durdur
        je .readStr_done

        ;karakter => buffer[SI]
        mov [si], al
        inc si

    jmp .readStr_loop

.readStr_done:
ret

;CIKTI
;al => karakter
readChar:
    mov ah,0x0
    int 0x16 
ret

;GIRDI
;si => str konumu
print:
    mov bx, 0
    
    .print_Loop:    
        lodsb
        cmp al, 0
        je .done

        call printChar
    jmp .print_Loop
    
.done
ret

;GIRDI
;al <= ekrana yazilacak karakter
printChar:    
    mov ah, 0x0e            
    int 0x10
ret