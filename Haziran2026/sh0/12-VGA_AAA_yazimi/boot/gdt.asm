gdt_nulldesc:
    dd 0
    dd 0

gdt_codedesc:
    dw 0xffff      ;limit
    dw 0x0000       ;base(low)
    db 0x00         ;base(medium)
    ;accessByte
    ;P(1), DPL(2), S(1), DC(1), RW(1), A(1)
    db 10011010b
    ;Flags
    ;G, DB, L, AVL, limit
    db 11001111b
    ;base
    db 0x00         ;base(high)

gdt_datadesc:
    dw 0xffff
    dw 0x0000
    db 0x00
    ;accessByte
    ;P(1), DPL(2), S(1), DC(1), RW(1), A(1)
    db 10010010b
    ;Flags
    ;G, DB, L, AVL, limit
    db 11001111b
    ;base
    db 0x00
gdt_end:

gdt_descriptor:
        dw gdt_end - gdt_nulldesc - 1
        dd gdt_nulldesc

codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc