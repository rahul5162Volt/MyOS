[org 0x7C00]
bits 16

jmp start

%include "boot/boot.inc"
%include "boot/print.asm"
%include "boot/disk.asm"

start:

    cli

    ;--------------------------------------
    ; Save BIOS boot drive
    ;--------------------------------------

    mov [boot_drive], dl

    ;--------------------------------------
    ; DS = CS
    ;--------------------------------------

    mov ax, cs
    mov ds, ax

    ;--------------------------------------
    ; Print Loading...
    ;--------------------------------------

    mov si, loading_msg
    call print_string

    ;--------------------------------------
    ; Load kernel (sector 2)
    ;--------------------------------------

    mov ax, KERNEL_SEGMENT
    mov es, ax
    mov bx, KERNEL_OFFSET

    mov dl, [boot_drive]

    mov al, 1          ; sectors
    mov ch, 0          ; cylinder
    mov cl, 2          ; sector
    mov dh, 0          ; head

    call disk_load

    jc disk_error

    ;--------------------------------------
    ; Success
    ;--------------------------------------

    mov si, ok_msg
    call print_string

.hang:
    jmp .hang

disk_error:

    mov si, error_msg
    call print_string

.error:
    jmp .error

boot_drive:
    db 0

loading_msg:
    db "Loading...",13,10,0

ok_msg:
    db "OK",13,10,0

error_msg:
    db "Disk Error",13,10,0

times 510-($-$$) db 0
dw 0xAA55