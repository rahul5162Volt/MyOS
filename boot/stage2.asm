[org 0x8000]

bits 16


start:


    cli


; Load kernel

    mov ax,0x1000
    mov es,ax

    xor bx,bx


    mov dl,[0x7DF0]


    mov ah,0x02
    mov al,1          ; kernel sectors

    mov ch,0
    mov cl,3          ; kernel starts sector 3

    mov dh,0

    mov ah,0x0E
    mov al,'R'
    int 0x10

    int 0x13

    jc disk_fail



; Enable A20

    in al,0x92

    or al,2

    out 0x92,al

    ; DEBUG
    mov ah,0x0E
    mov al,'A'
    int 0x10



; Load GDT

    lgdt [gdt_descriptor]

    mov ah,0x0E
    mov al,'B'
    int 0x10

; Protected mode

    mov eax,cr0
    or eax,1
    mov cr0,eax


    jmp 0x08:dword protected


disk_fail:

    cli

.hang:
    hlt
    jmp .hang


bits 32

protected:

    mov ax,0x10

    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax


    mov esp,0x90000


    mov byte [0xB8000],'S'
    mov byte [0xB8001],0x07


    mov eax,0x10000
    jmp eax




; ==================
; GDT
; ==================


gdt_start:


dq 0


; code

dw 0xffff
dw 0
db 0
db 10011010b
db 11001111b
db 0


; data

dw 0xffff
dw 0
db 0
db 10010010b
db 11001111b
db 0



gdt_end:



gdt_descriptor:

dw gdt_end-gdt_start-1

dd gdt_start