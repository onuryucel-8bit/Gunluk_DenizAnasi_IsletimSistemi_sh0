org 0x7C00
bits 16

main:

    ;std::cin >> sayi1;
    ;sayi1 = (int)sayi1;
    ;===================;
    mov ah,0x0
    int 0x16            
    call printChar
        
    sub al, '0' ;ASCII => int
    mov [sayi1], al
    ;===================;

    ;std::cin >> sayi2;
    ;sayi2 = (int)sayi2;
    ;===================;
    mov ah,0x0
    int 0x16  

    call printChar
    sub al, '0'
    mov [sayi2], al
    ;===================;


    ;sayi1 + sayi2
    ;===================;
    ;sayi1 => al    
    mov al, [sayi1]

    ;al + sayi2
    add al, [sayi2]
    
    add al, '0' ;int => ASCII
    mov [sayi1], al
    ;===================;

    
    ;std::cout << sonuc << "\n";
    ;===================;
    ;imleci en sola gonder
    mov al, 0x0D
    call printChar

    ;print('\n')
    mov al, 0x0A
    call printChar
    
    mov al, [sayi1]
    call printChar
    ;===================;


jmp $


;al => ekrana yazilacak karakter
printChar:    
    mov ah, 0x0e            
    int 0x10
ret

sayi1: db 0
sayi2: db 0


times 510-($-$$) db 0
dw 0xAA55