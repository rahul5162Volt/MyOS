bits 16

%include "memory.inc"

; ================================================================
; Load kernel from disk using BIOS INT 13h Extensions (LBA)
; ================================================================

disk_load_kernel:
    mov dl, [BOOT_DRIVE_ADDRESS]
    mov si, disk_address_packet
    mov ah, 0x42
    int 0x13
    jc disk_fail

    mov byte [0xB8000], 'K'
    mov byte [0xB8001], 0x0F

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
    ; 1000:0000 = physical 0x10000
    dw 0x0000
    dw KERNEL_LOAD_SEGMENT

    ; Zero-based starting LBA
    dq KERNEL_START_SECTOR - 1


; ================================================================
; Disk failure
; ================================================================

disk_fail:

    cli

.hang:
    hlt
    jmp .hang