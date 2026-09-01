# --------------------------------------------------
# Kernel
# --------------------------------------------------

set(KERNEL_SOURCES
    ${MYOS_ROOT}/kernel/kernel.c
    ${MYOS_ROOT}/kernel/io/io.c

    ${DRIVER_SOURCES}
    ${FILESYSTEM_SOURCES}
)

# --------------------------------------------------
# Kernel objects
# --------------------------------------------------

add_library(kernel_objects OBJECT
    ${KERNEL_SOURCES}
    ${EDITOR_SOURCES}
    ${UI_SOURCES}
)

# --------------------------------------------------
# Common C compiler options
# --------------------------------------------------

target_compile_options(
    kernel_objects
    PRIVATE
        -m32
        -ffreestanding
        -fno-stack-protector
        -fno-pie
)

# --------------------------------------------------
# Kernel entry
# --------------------------------------------------

add_library(kernel_entry OBJECT
    ${MYOS_ROOT}/kernel/kernel_entry.asm
)

# --------------------------------------------------
# Kernel ELF
# --------------------------------------------------

add_executable(kernel.elf
    $<TARGET_OBJECTS:kernel_entry>
    $<TARGET_OBJECTS:kernel_objects>
)

set_target_properties(kernel.elf PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${MYOS_BUILD}
    SUFFIX ""
)

target_link_options(kernel.elf PRIVATE
    -nostdlib
    -nodefaultlibs
    -nostartfiles
    -Wl,-m,elf_i386
    -T${MYOS_ROOT}/linker/linker.ld
)

set(KERNEL_ELF ${MYOS_BUILD}/kernel.elf)

add_custom_target(kernel_elf
    DEPENDS kernel.elf
)

# --------------------------------------------------
# Kernel binary
# --------------------------------------------------

set(KERNEL_BIN ${MYOS_BUILD}/kernel.bin)

add_custom_command(
    OUTPUT ${KERNEL_BIN}

    COMMAND i686-elf-objcopy
            -O binary
            ${KERNEL_ELF}
            ${KERNEL_BIN}

    COMMAND powershell
            -NoProfile
            -Command
            "if ((Get-Item '${KERNEL_BIN}').Length -gt ${KERNEL_BYTES}) { Write-Error 'Kernel is too large'; exit 1 }; fsutil file seteof '${KERNEL_BIN}' ${KERNEL_BYTES}"

    DEPENDS ${KERNEL_ELF}

    COMMENT "Creating kernel binary..."
)

add_custom_target(kernel_bin
    DEPENDS ${KERNEL_BIN}
)