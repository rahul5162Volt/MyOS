# --------------------------------------------------
# Bootloader
# --------------------------------------------------

set(BOOT_BIN ${MYOS_BUILD}/boot.bin)

add_custom_command(
    OUTPUT ${BOOT_BIN}

    COMMAND nasm
            -f bin
            ${MYOS_ROOT}/boot/boot.asm
            -o ${BOOT_BIN}

    DEPENDS
        ${MYOS_ROOT}/boot/boot.asm

    COMMENT "Building bootloader..."
)

add_custom_target(
    bootloader
    DEPENDS ${BOOT_BIN}
)

# --------------------------------------------------
# Stage 2
# --------------------------------------------------

set(STAGE2_BIN ${MYOS_BUILD}/stage2.bin)

add_custom_command(
    OUTPUT ${STAGE2_BIN}

    COMMAND nasm
            -D KERNEL_SECTORS=${KERNEL_SECTORS}
            -f bin
            ${MYOS_ROOT}/boot/stage2.asm
            -o ${STAGE2_BIN}

    COMMAND powershell
            -NoProfile
            -Command
            "if ((Get-Item '${STAGE2_BIN}').Length -gt 512) { Write-Error 'Stage2 is too large'; exit 1 }; fsutil file seteof '${STAGE2_BIN}' 512"

    DEPENDS
        ${MYOS_ROOT}/boot/stage2.asm

    COMMENT "Building Stage 2..."
)

add_custom_target(
    stage2
    DEPENDS ${STAGE2_BIN}
)