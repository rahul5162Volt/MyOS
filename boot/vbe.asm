bits 16

%include "vbe.inc"

vbe_init:
    ; Request VBE 2.0+ information.
    mov dword [VBE_INFO_ADDRESS], 'VBE2'

    xor ax, ax
    mov es, ax

    mov di, VBE_INFO_ADDRESS

    mov ax, 0x4F00
    int 0x10

    cmp ax, 0x004F
    jne vbe_fail

    ; Get VBE mode list.
    mov di, word [VBE_INFO_ADDRESS + 0x0E]
    mov ax, word [VBE_INFO_ADDRESS + 0x10]
    mov es, ax

    mov [vbe_mode_list_offset], di
    mov [vbe_mode_list_segment], es

    call vbe_find_mode

    ; Activate selected mode with linear framebuffer enabled.
    mov bx, [vbe_current_mode]
    or bx, 0x4000

    mov ax, 0x4F02
    int 0x10

    cmp ax, 0x004F
    jne vbe_fail

    ret


vbe_find_mode:
    mov ax, [vbe_mode_list_segment]
    mov es, ax

    mov di, [vbe_mode_list_offset]
    mov cx, [es:di]

    cmp cx, 0xFFFF
    je vbe_fail

    mov [vbe_current_mode], cx

    add di, 2
    mov [vbe_mode_list_offset], di

    xor ax, ax
    mov es, ax

    mov di, VBE_MODE_INFO_ADDRESS

    mov ax, 0x4F01
    mov cx, [vbe_current_mode]
    int 0x10

    cmp ax, 0x004F
    jne vbe_fail

    ; Check linear framebuffer support.
    mov ax, word [VBE_MODE_INFO_ADDRESS + 0x00]
    test ax, 0x0080
    jz vbe_find_mode

    ; Check resolution.
    mov ax, word [VBE_MODE_INFO_ADDRESS + 0x12]
    cmp ax, VBE_TARGET_WIDTH
    jne vbe_find_mode

    mov ax, word [VBE_MODE_INFO_ADDRESS + 0x14]
    cmp ax, VBE_TARGET_HEIGHT
    jne vbe_find_mode

    ; Check color depth.
    mov al, byte [VBE_MODE_INFO_ADDRESS + 0x19]
    cmp al, VBE_TARGET_BPP
    jne vbe_find_mode

    ret


vbe_fail:
    cli

.hang:
    hlt
    jmp .hang