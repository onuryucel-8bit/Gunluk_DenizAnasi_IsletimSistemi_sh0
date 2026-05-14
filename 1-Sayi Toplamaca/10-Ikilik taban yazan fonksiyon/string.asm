
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