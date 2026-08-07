bits 16


org 0x8000


start:


    cli


; --------------------
; Enable A20
; --------------------

    in al,0x92
    or al,00000010b
    out 0x92,al



; --------------------
; Load GDT
; --------------------

    lgdt [gdt_descriptor]



; --------------------
; Enter Protected Mode
; --------------------

    mov eax,cr0
    or eax,1
    mov cr0,eax



    jmp 0x08:protected_mode



bits 32


protected_mode:


    mov ax,0x10

    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax



    mov esp,0x90000



; jump to loaded kernel

    call 0x10000



.hang:

    jmp .hang




; ====================
; GDT
; ====================


gdt_start:


dq 0



; code segment

dw 0xffff
dw 0x0000
db 0x00
db 10011010b
db 11001111b
db 0x00



; data segment

dw 0xffff
dw 0x0000
db 0x00
db 10010010b
db 11001111b
db 0x00



gdt_end:



gdt_descriptor:

dw gdt_end-gdt_start-1
dd gdt_start