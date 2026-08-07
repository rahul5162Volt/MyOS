bits 16


disk_load:

    pusha


    mov ah,0x02


    int 0x13


    jc disk_failed



    popa

    clc

    ret



disk_failed:

    popa

    stc

    ret