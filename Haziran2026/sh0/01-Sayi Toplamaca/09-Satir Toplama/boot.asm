org 0x7C00
bits 16

;CR: Carriage Return
%define KEY_ENTER 0x0D
;'\n'
%define NEWLINE 0x0A

%define Ascii_to_int sub al, '0'
%define Int_to_ascii add al, '0'

main:
    ;print("sayi_1")
    mov si, girdiStr
    call print
    
    ;std::cin >> buffer;
    ;klavye girdisi => buffer
    mov si, buffer
    call read
        
    ;strcpy(buffer => sayi2, 10);
    ;kopyalama
    ;buffer => sayi2
    mov si, buffer
    mov di, sayi2
    mov cx, 10
    call strcpy
           
    ;ascii => int
    mov si, sayi2
    mov di, sayi2   
    call arrAsciiToInt

    ;imleci sola kaydir
    mov al, NEWLINE
    call printChar

    ;imleci asagi gonder
    mov al, KEY_ENTER
    call printChar

    ;print("sayi_2")
    mov si, girdiStr2
    call print

    ;std::cin >> buffer;
    ;klavye girdisi => buffer
    mov si, buffer
    call read

    ;imleci sola kaydir
    mov al, NEWLINE
    call printChar

    ;imleci asagi gonder
    mov al, KEY_ENTER
    call printChar

    
    ;ascii => int
    mov si, buffer
    mov di, buffer  
    call arrAsciiToInt
    
    ;buffer[i] += sayi2[i]

    ;cx = i
    mov cx, 10
    mov si, buffer
    mov di, sayi2
    
    .l0_toplama:
        ;al = buffer[si]
        lodsb
        ;al += sayi2[di]
        add al, [di]

        inc di
        Int_to_ascii
        call printChar
        dec cx
        cmp cx, 0
        jne .l0_toplama


jmp $


;GIRDI
;si <= kaynak ascii
;di <= donusum sonucu int
arrAsciiToInt:
    .l0_loop:
        
        lodsb
        
        cmp al, 0
        je .l0_done

        Ascii_to_int                
        stosb

        jmp .l0_loop
    .l0_done:
ret



%include "io.asm"
%include "string.asm"

;10 bayt yer ayriliyor
buffer: times 10 db 0
;10 bayt yer ayriliyor
sayi2: times 10 db 0

girdiStr: db "sayi_1: ",0
girdiStr2: db "sayi_2: ",0


;bootloader boyutu => SIZE
%assign SIZE ($ - $$)
;print("Bootloader size = " + str(SIZE) + "bytes")
%warning "Bootloader boyutu = " %str(SIZE) " bayt"

;kullanilabilir alan boyutu
%assign SIZE_empty(510 - SIZE)
%warning "Bootloader boyutu = " %str(SIZE_empty) " bayt"

times 510-($-$$) db 0
dw 0xAA55

