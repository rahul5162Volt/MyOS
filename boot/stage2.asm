bits 16

org 0x8000


start:


    cli


    mov [boot_drive],dl



; --------------------------
; Load kernel
; --------------------------


    mov ax,0x1000
    mov es,ax

    xor bx,bx


    mov dl,[boot_drive]


    mov al,1          ; kernel sectors

    mov ch,0
    mov cl,3          ; kernel starts sector 3

    mov dh,0



    call disk_load




; --------------------------
; Enable A20
; --------------------------

    in al,0x92

    or al,00000010b

    out 0x92,al



; --------------------------
; Load GDT
; --------------------------

    lgdt [gdt_descriptor]



; --------------------------
; Enter Protected Mode
; --------------------------

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



; Debug marker

    mov byte [0xB8000],'S'
    mov byte [0xB8001],0x07



; Jump kernel

    mov eax,0x10000

    jmp eax




; =========================
; GDT
; =========================


gdt_start:


dq 0



; Code descriptor

dw 0xffff

dw 0

db 0

db 10011010b

db 11001111b

db 0



; Data descriptor

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



boot_drive:

db 0



%include "boot/disk.asm"