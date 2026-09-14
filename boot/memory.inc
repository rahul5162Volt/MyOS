%ifndef MEMORY_INC
%define MEMORY_INC

; ================================================================
; MyOS physical memory layout
; ================================================================

; Stage 2 bootloader
%define STAGE2_LOAD_ADDRESS       0x8000

; Kernel
%define KERNEL_LOAD_ADDRESS       0x10000
%define KERNEL_LOAD_SEGMENT       0x1000

; Video information passed from stage2 to the kernel
%define VIDEO_INFO_ADDRESS        0x9000

; Real-mode stack
%define REAL_MODE_STACK           0x7000

; Protected-mode kernel stack
%define PROTECTED_MODE_STACK      0x90000

%define BOOT_DRIVE_ADDRESS        0x7DF0

%endif