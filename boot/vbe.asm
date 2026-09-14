bits 16

%include "vbe.inc"


; ================================================================
; Initialize VBE
; ================================================================

vbe_init:

    ; ------------------------------------------------------------
    ; Request VBE 2.0+ information.
    ; ------------------------------------------------------------

    mov dword [VBE_INFO_ADDRESS], 'VBE2'

    xor ax, ax
    mov es, ax

    mov di, VBE_INFO_ADDRESS

    mov ax, 0x4F00
    int 0x10

    cmp ax, 0x004F
    jne vbe_fail

    ; ------------------------------------------------------------
    ; Get VBE mode list pointer.
    ; ------------------------------------------------------------

    mov di, [VBE_INFO_ADDRESS + 0x0E]
    mov ax, [VBE_INFO_ADDRESS + 0x10]

    mov [vbe_mode_list_offset], di
    mov [vbe_mode_list_segment], ax

    ; ------------------------------------------------------------
    ; Search for the required mode.
    ; ------------------------------------------------------------

    call vbe_find_mode

    ; ------------------------------------------------------------
    ; Activate selected mode with Linear Framebuffer enabled.
    ; ------------------------------------------------------------

    mov bx, [vbe_current_mode]
    or bx, 0x4000

    mov ax, 0x4F02
    int 0x10

    cmp ax, 0x004F
    jne vbe_fail

    ret


; ================================================================
; Find 1024x768x32 linear framebuffer mode
; ================================================================

vbe_find_mode:

.next_mode:

    ; ------------------------------------------------------------
    ; Read next mode number from VBE mode list.
    ; ------------------------------------------------------------

    mov ax, [vbe_mode_list_segment]
    mov es, ax

    mov di, [vbe_mode_list_offset]

    mov cx, [es:di]

    ; End of mode list.
    cmp cx, 0xFFFF
    je vbe_fail

    ; Advance to next mode for the next iteration.
    add di, 2
    mov [vbe_mode_list_offset], di

    ; Save current candidate.
    mov [vbe_current_mode], cx

    ; ------------------------------------------------------------
    ; Get mode information.
    ; ------------------------------------------------------------

    xor ax, ax
    mov es, ax

    mov di, VBE_MODE_INFO_ADDRESS

    mov ax, 0x4F01
    int 0x10

    cmp ax, 0x004F
    jne .next_mode

    ; ------------------------------------------------------------
    ; Check Linear Framebuffer support.
    ; Mode attributes bit 7 must be set.
    ; ------------------------------------------------------------

    mov ax, [VBE_MODE_INFO_ADDRESS + 0x00]
    test ax, 0x0080
    jz .next_mode

    ; ------------------------------------------------------------
    ; Check width.
    ; ------------------------------------------------------------

    mov ax, [VBE_MODE_INFO_ADDRESS + 0x12]
    cmp ax, VBE_TARGET_WIDTH
    jne .next_mode

    ; ------------------------------------------------------------
    ; Check height.
    ; ------------------------------------------------------------

    mov ax, [VBE_MODE_INFO_ADDRESS + 0x14]
    cmp ax, VBE_TARGET_HEIGHT
    jne .next_mode

    ; ------------------------------------------------------------
    ; Check bits per pixel.
    ; ------------------------------------------------------------

    mov al, [VBE_MODE_INFO_ADDRESS + 0x19]
    cmp al, VBE_TARGET_BPP
    jne .next_mode

    ; ------------------------------------------------------------
    ; Required mode found.
    ;
    ; Now copy only the information the kernel needs.
    ; ------------------------------------------------------------

    mov ax, [VBE_MODE_INFO_ADDRESS + 0x10]
    mov [vbe_pitch], ax

    mov ax, [VBE_MODE_INFO_ADDRESS + 0x12]
    mov [vbe_width], ax

    mov ax, [VBE_MODE_INFO_ADDRESS + 0x14]
    mov [vbe_height], ax

    mov al, [VBE_MODE_INFO_ADDRESS + 0x19]
    mov [vbe_bpp], al

    mov eax, [VBE_MODE_INFO_ADDRESS + 0x28]
    mov [vbe_framebuffer], eax

    ret


; ================================================================
; VBE failure
; ================================================================

vbe_fail:
    cli

.hang:
    hlt
    jmp .hang