[org 0x7c00]
bits 16

%define ASCII_KEY_ENTER 0x0D    ;CR: Carriage Return
%define ASCII_NEWLINE 0x0A      ;'\n'
%define ASCII_COLON 0x3A        ;':'
%define ASCII_A 0x41            ;'A'

%macro mac_asagiSatiraGec 0
    ;imleci sola kaydir
    mov al, ASCII_NEWLINE
    call printChar

    ;imleci asagi gonder
    mov al, ASCII_KEY_ENTER
    call printChar
%endmacro

main:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    
    mov ax, 0x9000
    mov ss, ax
    mov sp, 0x9FFF

    mov si, loadMsg
    call printString

    mac_asagiSatiraGec

    call EnableA20
            
    
    mov bx, 0x7e00
    mov dh, 1
    call fn_read_sectors

    cli

    ;gdt tablosunu yukle
    lgdt [gdt_descriptor]

    ;PM moda gec
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp codeseg:StartPM

fn_read_sectors:
    mov ah, 0x02
    mov al, dh
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    int 0x13
    jc disk_error
ret

    
disk_error:
    mov si, errorMsg
    call printString
    jmp $
    
printString:
.next_char:
    lodsb
    cmp al, 0
    je .done
    mov ah, 0x0e
    int 0x10
    jmp .next_char
.done:
ret

;GIRDI
;al <= ekrana yazilacak karakter
printChar:
    mov ah, 0x0e            
    int 0x10
ret

EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
ret

%include "boot\gdt.asm"

loadMsg: db "Kernel yukleniyor...",0
errorMsg: db "Kernel acilmadi... :|",0

[bits 32]

StartPM:

    mov ax, dataseg

    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    mov esp, 0x90000

    jmp 0x7E00

times 510-($-$$) db 0
dw 0xAA55