;==========================================
; MyOS Boot Constants
;==========================================

%ifndef BOOT_INC
%define BOOT_INC

BOOT_LOAD_ADDRESS equ 0x7C00

BOOT_SEGMENT equ 0x07C0

KERNEL_SEGMENT equ 0x1000
KERNEL_OFFSET  equ 0x0000

BOOT_SECTOR_SIZE equ 512

%endif