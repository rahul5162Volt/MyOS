bits 16

global start

extern kernel_main

start:

    call kernel_main

.hang:
    jmp .hang