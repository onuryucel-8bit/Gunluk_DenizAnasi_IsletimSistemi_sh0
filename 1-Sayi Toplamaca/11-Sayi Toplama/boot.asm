[org 0]
bits 16

%include "asciiTable.asm"

%define Ascii_to_int sub al, '0'
%define Int_to_ascii add al, '0'

;sifir argumanli yeni satir makrosu
%macro mac_asagiSatiraGec 0
    ;imleci sola kaydir
    mov al, ASCII_NEWLINE
    call printChar

    ;imleci asagi gonder
    mov al, ASCII_KEY_ENTER
    call printChar
%endmacro

%macro mac_bellegiYazdir 1
    mov dx, %1
    call printBinary
%endmacro

%macro mac_stdcoutSTR 1
    mov si, %1
    call print
%endmacro

%macro mac_stdcin 1
    mov si, %1
    call read
%endmacro

jmp 0x7c0:main

main:

;----------------------------------------------------------------------------------;
;----------------------------------------------------------------------------------;
    cli ;kesmeleri kapat

    ;segment bellekleri ayarlaniyor
    mov ax, 0x7c0
    mov ds, ax
    mov es, ax

    ;yigin ayarlama
    mov ax, 0x9000
    mov ss, ax
    mov sp, 0xFFFF 
    sti ;kesmeleri ac
;----------------------------------------------------------------------------------;
;----------------------------------------------------------------------------------;

;==============================;
;==============================;
;   std::cout << "sayi_1";
;   std::cin >> buffer;
;
;   std::cout << std::hex << buffer;
;    
;   sayi_2 = buffer;
;   sayi_2 = (int)sayi_2;
;   
;   std::cout << "\n";
;
;   std::cout << "sayi_2";   
;   std::cin >> buffer;
;   
;   std::cout << "\n";
;   
;   buffer = (int)buffer;
;   sayi_2 += buffer;
;   
;   std::cout << 0b(sayi_2);
;==============================;
;==============================;
    
    mac_stdcoutSTR girdiStr
    
    mac_stdcin sayi2
               
    ;sayi2 = (int)sayi2;
    ;----------------;
    mov si, sayi2
    mov di, sayi2
    call arrAsciiToInt
               
    mov di, sayi2
    mov [di], dx

    mac_asagiSatiraGec
    call printHex
    ;----------------;

    ;std::cout << "\n sayi_2:";
    ;----------------;
    mac_asagiSatiraGec
    mac_stdcoutSTR girdiStr2        
    ;----------------;

    ;----------------;
    mac_stdcin buffer
    mac_asagiSatiraGec
    ;----------------;
    
    ;----------------;
    ;buffer =(int)buffer
    ;std::cout << std::hex << buffer;
    mov si, buffer
    mov di, buffer
    call arrAsciiToInt
    call printHex
    ;----------------;


    ;----------------;
    mac_asagiSatiraGec
    ;sayi2 += buffer
    mov ax, [sayi2]
    add dx, ax
    ;----------------;

    ;std::cout << "sonuc = ";
    ;----------------;
    mac_asagiSatiraGec
    mov si, sonucStr    
    call print
    ;----------------;    

    ;std::cout << sayi + buffer;
    ;----------------;
    call printHex
    mac_asagiSatiraGec
    ;----------------;

    ;sayi = 0;
    ;buffer = 0;
    ;----------------;
    mov di, buffer
    mov cx, 10
    call clearMemory

    mov di, sayi2
    mov cx, 10
    call clearMemory
    ;----------------;

jmp main                




%include "memory.asm"
%include "io.asm"
%include "string.asm"

;10 bayt yer ayriliyor
buffer: times 10 db 0
;10 bayt yer ayriliyor
sayi2: times 10 db 0

girdiStr: db "sayi_1: ",0
girdiStr2: db "sayi_2: ",0
sonucStr: db "sonuc = ",0


;bootloader boyutu => SIZE
%assign SIZE ($ - $$)
;print("Bootloader size = " + str(SIZE) + "bytes")
%warning "Bootloader boyutu = " %str(SIZE) " bayt"

;kullanilabilir alan boyutu
%assign SIZE_empty(510 - SIZE)
%warning "Kullanilabilir alan boyutu = " %str(SIZE_empty) " bayt"

times 510-($-$$) db 0
dw 0xAA55

