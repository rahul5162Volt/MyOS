[org 0x7C00]

bits 16


start:

    cli

    mov ax,0x0000
    mov ds,ax

    mov [BOOT_DRIVE],dl


    mov si,msg
    call print


; Load stage2

    mov ax,0x0800
    mov es,ax

    xor bx,bx


    mov dl,[BOOT_DRIVE]

    mov ah,0x02
    mov al,1          ; stage2 = 1 sector

    mov ch,0
    mov cl,2
    mov dh,0


    int 0x13

    jc disk_error

    mov [0x7DF0], dl

    jmp 0x0800:0x0000



disk_error:

    mov si,error
    call print


hang:

    jmp hang



print:

    mov ah,0x0E


.loop:

    lodsb

    cmp al,0
    je .done

    int 0x10

    jmp .loop


.done:

    ret



BOOT_DRIVE:

db 0


msg:

db "Loading Stage2...",13,10,0


error:

db "Disk Error",0



times 510-($-$$) db 0

dw 0xAA55
