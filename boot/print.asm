bits 16

;------------------------------------------
; print_string
; DS:SI -> zero terminated string
;------------------------------------------

print_string:

.loop:

    mov al, [si]

    cmp al, 0
    je .done

    mov ah, 0x0E
    int 0x10

    inc si

    jmp .loop

.done:

    ret