;for(i = 0; i < boyut(cx); i++)
;   ram[di] = 0;
;GIRDI
;di <= adres
;cx <= boyut
clearMemory:
    xor al,al
    rep stosb    
ret