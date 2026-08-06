[org 0x7C00]
bits 16

jmp start

%include "boot/boot.inc"
%include "boot/print.asm"
%include "boot/disk.asm"

start:

    cli

    ; Save BIOS boot drive
    mov [boot_drive], dl

    ; DS = CS
    mov ax, cs
    mov ds, ax

    ; Print Loading...
    mov si, loading_msg
    call print_string

    ; Read sector 2 -> 0x1000:0000
    mov ax, KERNEL_SEGMENT
    mov es, ax
    xor bx, bx

    mov dl, [boot_drive]

    mov al, 1
    mov ch, 0
    mov cl, 2
    mov dh, 0

    call disk_load

    jc disk_error

    ; Print OK
    mov si, ok_msg
    call print_string

    ; Verify loaded kernel
    mov ax, KERNEL_SEGMENT
    mov ds, ax

    mov al, [0]
    call print_char

.hang:
    jmp .hang

disk_error:

    mov ax, cs
    mov ds, ax

    mov si, error_msg
    call print_string

.error:
    jmp .error

boot_drive:
    db 0

loading_msg:
    db "Loading...",13,10,0

ok_msg:
    db "OK ",0

error_msg:
    db "Disk Error",13,10,0

times 510-($-$$) db 0
dw 0xAA55