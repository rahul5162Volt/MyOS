bits 32


global start

extern kernel_main



section .text



start:


mov esp,0x90000


call kernel_main



.hang:

jmp .hang