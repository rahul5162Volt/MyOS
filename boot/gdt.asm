gdt_start:

; Null descriptor
dq 0x0000000000000000


; Code segment
; Selector = 0x08

dw 0xffff
dw 0x0000
db 0x00
db 10011010b
db 11001111b
db 0x00


; Data segment
; Selector = 0x10

dw 0xffff
dw 0x0000
db 0x00
db 10010010b
db 11001111b
db 0x00


gdt_end:


gdt_descriptor:

dw gdt_end - gdt_start - 1
dd gdt_start