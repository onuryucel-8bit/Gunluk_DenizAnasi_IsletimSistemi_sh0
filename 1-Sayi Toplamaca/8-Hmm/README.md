stosb di belleginin gosterdigi adrese al icindeki bayti yerlestirir

```asm

;[di] = al,
;di++
stosb    

;stosb ve lodsb imleclerini ileriye dogru kaydirmayi acar
;lodsb si++/stosb di++ olur 
;eger std komutu kullanilirsa
;lodsb si--/stosb di-- olur

cld 
std

```