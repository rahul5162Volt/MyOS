bits 16

global enter_protected_mode

enter_protected_mode:

    cli

    ; Enable Protected Mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Flush pipeline and load new CS
    jmp 0x08:protected_mode


;=================================================
; 32-bit Code
;=================================================

bits 32

protected_mode:

    ; Load data selector
    mov ax, 0x10

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Stack
    mov esp, 0x90000

    ; VGA memory
    mov edi, 0xB8000

    mov word [edi], 0x0F50      ; P
    mov word [edi+2], 0x0F4D    ; M

.hang:
    cli
    hlt
    jmp .hang