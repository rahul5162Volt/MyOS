%ifndef KERNEL_SECTORS
%define KERNEL_SECTORS 8
%endif

[org 0x8000]

bits 16

start:
    cli

    xor ax, ax
    mov ds, ax

    ; Load kernel to physical address 0x10000.
    mov ax, 0x1000
    mov es, ax
    xor bx, bx

    mov dl, [0x7DF0]

    mov ah, 0x02
    mov al, KERNEL_SECTORS
    mov ch, 0
    mov cl, 3
    mov dh, 0
    int 0x13
    jc disk_fail

    ; Enable A20.
    in al, 0x92
    or al, 2
    out 0x92, al

    ; Load the protected-mode GDT.
    lgdt [gdt_descriptor]

    ; Enable protected mode.
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp dword 0x08:protected_mode

disk_fail:
    cli
.hang:
    hlt
    jmp .hang

bits 32

protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000
    cld

    ; Kernel entry is linked and loaded at 0x10000.
    mov eax, 0x10000
    jmp eax

gdt_start:
    dq 0

    ; Code segment: base 0, limit 4 GiB.
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

    ; Data segment: base 0, limit 4 GiB.
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