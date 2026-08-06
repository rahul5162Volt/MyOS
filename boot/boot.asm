[org 0x7C00]
bits 16

jmp start

%include "boot/boot.inc"
%include "boot/print.asm"

start:

    cli

    xor ax, ax
    mov ds, ax

    mov si, message
    call print_string

.hang:
    jmp .hang

message:
    db "Hello MyOS!", 0

times 510-($-$$) db 0
dw 0xAA55