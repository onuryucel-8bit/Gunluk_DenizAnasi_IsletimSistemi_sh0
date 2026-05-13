
;GIRDI
;SI <= Kopyalanacak verinin baslangic adresi
;DI <= Verinin yazilacagi adres
strcpy:
    ;al = ram[si]
    ;si++
    lodsb

    mov [di], si

ret