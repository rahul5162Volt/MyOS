bits 16

disk_load:

    mov ah, 0x02
    int 0x13

    ret