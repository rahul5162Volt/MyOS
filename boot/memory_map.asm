bits 16

; ================================================================
; BIOS E820 memory map
; ================================================================

memory_map_detect:
    xor ax, ax
    mov es, ax

    xor ebx, ebx
    mov di, MEMORY_MAP_ADDRESS
    mov word [MEMORY_MAP_COUNT_ADDRESS], 0

.next:
    mov eax, 0xE820
    mov edx, 0x534D4150
    mov ecx, 24
    int 0x15

    jc .done

    cmp eax, 0x534D4150
    jne .done

    inc word [MEMORY_MAP_COUNT_ADDRESS]
    add di, 24

    cmp word [MEMORY_MAP_COUNT_ADDRESS], MEMORY_MAP_MAX_ENTRIES
    jae .done

    test ebx, ebx
    jnz .next

.done:
    ret