
;GIRDI
;SI <= Kopyalanacak verinin baslangic adresi
;DI <= Verinin yazilacagi adres
;CX <= Kopyalama miktari
strcpy:

    ;di/sl ++
    cld
    
    .strcpy_loop:        
        cmp cx, 0
        je .strcpy_done

        ;al = ram[si]
        ;si++
        lodsb

        ;[di] = al,
        ;di++
        stosb               
        
        ;kopyalanan verinin sonuna gelindimi
        cmp al, 0
        je .strcpy_done
        
        ;kopyalama sayacini azalt
        dec cx
    
        jmp .strcpy_loop


.strcpy_done:
ret

;for (int i = 0; str[i] != '\0'; i++) 
;{
;    num = num * 10 + (str[i] - 48);
;}
;GIRDI
;si <= kaynak ascii
;CIKTI
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