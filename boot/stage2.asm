%ifndef KERNEL_SECTORS
%define KERNEL_SECTORS 32
%endif

%ifndef STAGE2_SECTORS
%define STAGE2_SECTORS 4
%endif

%define KERNEL_START_SECTOR (2 + STAGE2_SECTORS)

[org 0x8000]

bits 16

%include "memory.inc"
%include "vbe.inc"


; ================================================================
; Stage 2 entry
; ================================================================

start:
    cli

    xor ax, ax
    mov ds, ax
    mov ss, ax
    mov sp, REAL_MODE_STACK

    call vbe_init

    ; Copy VBE information to the kernel video_info structure
    mov ax, [vbe_pitch]
    mov [VIDEO_INFO_ADDRESS], ax

    mov ax, [vbe_width]
    mov [VIDEO_INFO_ADDRESS + 2], ax

    mov ax, [vbe_height]
    mov [VIDEO_INFO_ADDRESS + 4], ax

    mov al, [vbe_bpp]
    mov [VIDEO_INFO_ADDRESS + 6], al

    mov eax, [vbe_framebuffer]
    mov [VIDEO_INFO_ADDRESS + 8], eax

    call disk_load_kernel

    in al, 0x92
    or al, 0x02
    out 0x92, al

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x01
    mov cr0, eax

    jmp dword 0x08:protected_mode


; ================================================================
; Protected mode
; ================================================================

bits 32

protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, PROTECTED_MODE_STACK
    cld
    
    ; ------------------------------------------------------------
    ; Jump to kernel
    ; ------------------------------------------------------------

    jmp 0x10000


; ================================================================
; GDT
; ================================================================

gdt_start:
    dq 0

    ; Code segment
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

    ; Data segment
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start


; ================================================================
; Stage 2 modules
; ================================================================

%include "vbe.asm"
%include "disk.asm"