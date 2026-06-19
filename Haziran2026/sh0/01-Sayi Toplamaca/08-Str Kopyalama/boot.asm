org 0x7C00
bits 16

;CR: Carriage Return
%define KEY_ENTER 0x0D
;'\n'
%define NEWLINE 0x0A

;klavye => str => kopya => ekran
main:
    
    ;klavye girdisi => buffer
    mov si, buffer
    call read
    
    ;buffer => ekran
    mov si, buffer
    call print
    
    ;kopyalama
    ;buffer => sayi2
    mov si, buffer
    mov di, sayi2
    mov cx, 10
    call strcpy

    ;imleci sola kaydir
    mov al, NEWLINE
    call printChar

    ;imleci asagi gonder
    mov al, KEY_ENTER
    call printChar

    ;sayi2 => ekran
    mov si, sayi2
    call print
jmp $

%include "io.asm"
%include "string.asm"

;10 bayt yer ayriliyor
buffer: times 10 db 0
;10 bayt yer ayriliyor
sayi2: times 10 db 0

;bootloader boyutu => SIZE
%assign SIZE ($ - $$)
;print("Bootloader size = " + str(SIZE) + "bytes")
%warning "Bootloader boyutu = " %str(SIZE) " bayt"

;kullanilabilir alan boyutu
%assign SIZE_empty(510 - SIZE)
%warning "Bootloader boyutu = " %str(SIZE_empty) " bayt"

times 510-($-$$) db 0
dw 0xAA55

