;GIRDI
;si <= klavye girdisinin tutulacagi adres
read:    

    .readStr_loop:

        call readChar
        ;karakter ?= KEY_ENTER
        call printChar
        cmp al, ASCII_KEY_ENTER
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
;si <= str konumu
print:
    mov bx, 0
    
    .print_Loop:    
        lodsb
        cmp al, 0
        je .print_done

        call printChar
    jmp .print_Loop
    
.print_done:
ret

;GIRDI
;al <= ekrana yazilacak karakter
printChar:
    mov ah, 0x0e            
    int 0x10
ret

;GIRDI
;dx <= ascii 16 Bit sayi
;CIKTI
;ikilik taban ciktisi high|low
printBinary:
    
    mov cx, 7
    mov bl, 0x80
    .printBinary_loop_dh:
        mov al, dh
        and al, bl
        
        shr bl, 1

        shr al, cx
        Int_to_ascii
        call printChar


        sub cx, 1
        cmp cx, -1
        jne .printBinary_loop_dh

    mov cx, 7
    mov bl, 0x80
    
    mov al, '|'
    call printChar

    .printBinary_loop_dl:
        mov al, dl
        and al, bl
        
        shr bl, 1

        shr al, cx
        Int_to_ascii
        call printChar


        sub cx, 1
        cmp cx, -1
        jne .printBinary_loop_dl

ret

;GIRDI
;dx <= on altilik sayi 0xffff
printHex:

    mov al, '0'
    call printChar
    mov al, 'x'
    call printChar

    mov cx, 12

    .printHex_loop:
        mov ax, dx
        shr ax, cx    
         
        and ax, 0x000f        
        Int_to_ascii
        cmp al, ASCII_COLON
        jl .printNumber
        ;a,b,c,d,e,f icin tabloda aradaki farki bulup ekleme yapiliyor        
        ;ornegin 0xA5FF
        ;ilk karakter A int_to_ascii sonucu ':' 0x3A bunu 7 ile kaydirirsak 'A'ascii olur
        ;F icin => '?' 7 kaydir => 'F'ascii olur
        add al, 7                                        
        .printNumber:
        call printChar                          
        
        sub cx, 4        
        cmp cx, 0
        ;if(cx >= 0) jmp
        jge .printHex_loop
ret