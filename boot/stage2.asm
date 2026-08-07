[org 0x8000]

bits 16

start:
    cli

    ; -----------------------------
    ; Initialize segments
    ; -----------------------------
    xor ax, ax
    mov ds, ax

    ; Debug: Stage2 started
    mov ah, 0x0E
    mov al, 'R'
    int 0x10

    ; -----------------------------
    ; Load kernel to 0x10000
    ; -----------------------------
    mov ax, 0x1000
    mov es, ax
    xor bx, bx

    mov dl, [0x7DF0]

    mov ah, 0x02
    mov al, 1
    mov ch, 0
    mov cl, 3
    mov dh, 0
    int 0x13
    jc disk_fail

    ; Debug: Kernel loaded
    mov ah, 0x0E
    mov al, 'A'
    int 0x10

    ; -----------------------------
    ; Enable A20
    ; -----------------------------
    in al, 0x92
    or al, 2
    out 0x92, al

    ; -----------------------------
    ; Load GDT
    ; -----------------------------
    lgdt [gdt_descriptor]

    ; -----------------------------
    ; Enter Protected Mode
    ; -----------------------------

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp dword 0x08:protected_mode


disk_fail:
    cli
.hang:
    hlt
    jmp .hang


; =====================================================
; 32-bit code
; =====================================================

bits 32

protected_mode:

    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax

    mov esp,0x90000

    cld

    mov byte [0xB8000],'S'
    mov byte [0xB8001],0x07

    mov byte [0xB8002],'K'
    mov byte [0xB8003],0x07

    mov eax, 0x10000
    jmp eax


; =====================================================
; GDT
; =====================================================

gdt_start:

dq 0

; Code segment
dw 0xFFFF
dw 0x0000
db 0x00
db 10011010b
db 11001111b
db 0x00

; Data segment
dw 0xFFFF
dw 0x0000
db 0x00
db 10010010b
db 11001111b
db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start