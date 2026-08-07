[org 0x8000]

bits 16

start:
    cli

    xor ax, ax
    mov ds, ax

    ; -----------------------------
    ; Debug: Stage2 started
    ; -----------------------------
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
    mov al, 2          ; Read 2 sectors (temporary)
    mov ch, 0
    mov cl, 3          ; Kernel starts at sector 3
    mov dh, 0

    int 0x13
    jc disk_fail

    ; -----------------------------
    ; Disk read succeeded
    ; -----------------------------
    mov ah, 0x0E
    mov al, 'A'
    int 0x10

    ; -----------------------------
    ; Show first byte of loaded kernel
    ; -----------------------------
    mov al, [es:0]

    cmp al, 0
    jne byte_ok

    mov al, '0'

byte_ok:
    mov ah, 0x0E
    int 0x10

hang:
    cli
    hlt
    jmp hang

disk_fail:
    mov ah, 0x0E
    mov al, 'F'
    int 0x10

    ; Print BIOS error code (AH)
    mov al, ah
    add al, '0'
    mov ah, 0x0E
    int 0x10

    cli
.fail:
    hlt
    jmp .fail