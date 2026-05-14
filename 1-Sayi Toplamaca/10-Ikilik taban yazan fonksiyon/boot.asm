[org 0x7C00]
bits 16

;CR: Carriage Return
%define KEY_ENTER 0x0D
;'\n'
%define NEWLINE 0x0A

%define Ascii_to_int sub al, '0'
%define Int_to_ascii add al, '0'

;sifir argumanli yeni satir makrosu
%macro mac_asagiSatiraGec 0
    ;imleci sola kaydir
    mov al, NEWLINE
    call printChar

    ;imleci asagi gonder
    mov al, KEY_ENTER
    call printChar
%endmacro

main:
    ;print("sayi_1")
    mov si, girdiStr
    call print
    
    ;std::cin >> buffer;
    ;klavye girdisi => buffer
    mov si, buffer
    call read
                       
    mac_asagiSatiraGec
       
    ;ascii => int
    mov si, buffer   
    call arrAsciiToInt
         
    call printBinary
    

    ;buffer[i] += sayi2[i]

jmp $


;for (int i = 0; str[i] != '\0'; i++) 
;{
;    num = num * 10 + (str[i] - 48);
;}
;GIRDI
;si <= kaynak ascii
;dx => donusum sonucu int
arrAsciiToInt:
    mov dx, 0
    .l0_loop:
        
        lodsb
        
        cmp al, 0
        je .l0_done
        
        Ascii_to_int
        mov cl, al


        ;num * 10
        ;dx *= 10
        mov ax, dx
        mov bx, 10
        ;ax *= bx(10)
        mul bx
        mov dx, ax

        ;ax kismini sifirla
        xor ax, ax
        ;al = cl
        mov al, cl
        ;dx += ax
        add dx, ax

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

