suan print fonksiyonunda hata var sebebi read arkaya '\0' koymadigi icin 
print fonksiyonu '\0' karakterini bulasiya kadar yazmaya devam ediyor 

```asm
;GIRDI
;si => str konumu
print:
    mov bx, 0
    
    .print_Loop:    
        lodsb
        cmp al, 0
        je .done

        call printChar
    jmp .print_Loop
    
.done
ret
```