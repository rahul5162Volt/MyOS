bits 16

start:

    mov ah, 0x0E

    mov al, 'K'
    int 0x10

    mov al, 'e'
    int 0x10

    mov al, 'r'
    int 0x10

    mov al, 'n'
    int 0x10

    mov al, 'e'
    int 0x10

    mov al, 'l'
    int 0x10

    mov al, '!'
    int 0x10

.hang:
    jmp .hang

times 512-($-$$) db 0