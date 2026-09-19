bits 16

%include "memory.inc"

; ================================================================
; Load kernel from disk using BIOS INT 13h Extensions (LBA / EDD)
; ================================================================

disk_load_kernel:
    mov dl, [BOOT_DRIVE_ADDRESS]

    ; ------------------------------------------------------------
    ; Check BIOS INT 13h Extensions support
    ; AH = 41h
    ; BX = 55AAh
    ; ------------------------------------------------------------

    mov ah, 0x41
    mov bx, 0x55AA
    int 0x13

    jc disk_fail

    cmp bx, 0xAA55
    jne disk_fail

    test cx, 0x0001
    jz disk_fail

    ; ------------------------------------------------------------
    ; Extended disk read
    ; AH = 42h
    ; DS:SI = Disk Address Packet
    ; ------------------------------------------------------------

    mov si, disk_address_packet
    mov ah, 0x42
    int 0x13

    jc disk_fail

    ret


; ================================================================
; Disk Address Packet
; ================================================================

align 4

disk_address_packet:

    ; DAP size
    db 0x10

    ; Reserved
    db 0x00

    ; Number of sectors
    dw KERNEL_SECTORS

    ; Destination buffer
    ; 1000:0000 = physical address 0x10000
    dw 0x0000
    dw KERNEL_LOAD_SEGMENT

    ; Zero-based starting LBA
    ;
    ; Existing boot layout uses BIOS sector numbering where
    ; KERNEL_START_SECTOR is the first kernel sector.
    ; Convert that to zero-based LBA.
    dq KERNEL_START_SECTOR - 1


; ================================================================
; Disk failure
; ================================================================

disk_fail:
    cli

.hang:
    hlt
    jmp .hang
    