[org 0x7C00]

bits 16


jmp start


%include "boot/boot.inc"
%include "boot/print.asm"
%include "boot/disk.asm"


start:

    cli


    mov [boot_drive], dl


    mov ax, cs
    mov ds, ax



    mov si, loading_msg
    call print_string



; --------------------------
; Load Stage2
; --------------------------

    mov ax,0x0800
    mov es,ax

    xor bx,bx


    mov dl,[boot_drive]

    mov al,1          ; stage2 is 114 bytes

    mov ch,0
    mov cl,2
    mov dh,0


    call disk_load


    jc disk_error



    mov si,ok_msg
    call print_string



    jmp 0x0800:0x0000




disk_error:

    mov si,error_msg
    call print_string


.hang:

    jmp .hang




boot_drive:

    db 0



loading_msg:

    db "Loading Stage2...",13,10,0



ok_msg:

    db "Stage2 Loaded",13,10,0



error_msg:

    db "Disk Error",13,10,0



times 510-($-$$) db 0

dw 0xAA55