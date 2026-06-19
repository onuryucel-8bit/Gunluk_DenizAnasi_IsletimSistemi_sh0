[org 0x7C00]
bits 16

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

mov ah, 2
mov al, 1     ;okunacak alan(sector) miktari
;silindir numarasi
mov ch, 0
;alan sayisi
mov cl, 2
;kafa numarasi
mov dh, 0
;mov dl,    BIOS yuklenme aninda bu kismi ayarlamakta

mov bx, yuklemeAlani

int 0x13
jc .yuklemeHatasi

mov si, yuklemeAlani
call print

jmp $


.yuklemeHatasi:
mov si, hataMesaji
call print

jmp $

hataMesaji: db "HATA:: DENIZ ANASI yuklenemedi..."


%include "std/io.asm"

times 510-($-$$) db 0
dw 0xAA55

yuklemeAlani: