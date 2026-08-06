;==========================================
; MyOS BIOS Print Routines
;==========================================

bits 16

;------------------------------------------
; print_char
;
; Input:
;   AL = character
;------------------------------------------

print_char:

    push ax

    mov ah, 0x0E
    int 0x10

    pop ax

    ret

;------------------------------------------
; print_string
;
; Input:
;   DS:SI -> zero terminated string
;------------------------------------------

print_string:

.next:

    lodsb

    cmp al, 0
    je .done

    call print_char

    jmp .next

.done:

    ret