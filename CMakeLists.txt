cmake_minimum_required(VERSION 4.0)

project(MyOS NONE)

# --------------------------------------------------
# Tools
# --------------------------------------------------

set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_ASM_NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

enable_language(C)
enable_language(ASM_NASM)

# --------------------------------------------------
# Paths
# --------------------------------------------------

set(MYOS_ROOT ${CMAKE_SOURCE_DIR})
set(MYOS_BUILD ${CMAKE_BINARY_DIR})

# --------------------------------------------------
# Kernel configuration
# --------------------------------------------------

set(KERNEL_SECTORS 32)
set(KERNEL_BYTES 16384)
set(OS_IMAGE_SIZE 1474560)

# --------------------------------------------------
# Include directories
# --------------------------------------------------

include_directories(
    ${MYOS_ROOT}/drivers
    ${MYOS_ROOT}/drivers/vga

    ${MYOS_ROOT}/kernel/io

    ${MYOS_ROOT}/filesystem/core

    ${MYOS_ROOT}/editor/core
    ${MYOS_ROOT}/editor/document
    ${MYOS_ROOT}/editor/clipboard
    ${MYOS_ROOT}/editor/cursor
    ${MYOS_ROOT}/editor/edit
    ${MYOS_ROOT}/editor/input
    ${MYOS_ROOT}/editor/lines
    ${MYOS_ROOT}/editor/navigation
    ${MYOS_ROOT}/editor/render
    ${MYOS_ROOT}/editor/selection
    ${MYOS_ROOT}/editor/text
    ${MYOS_ROOT}/editor/undo
)

# --------------------------------------------------
# Kernel sources
# --------------------------------------------------

set(KERNEL_SOURCES
    ${MYOS_ROOT}/kernel/kernel.c
    ${MYOS_ROOT}/kernel/io/io.c

    ${MYOS_ROOT}/drivers/keyboard/keyboard.c
    ${MYOS_ROOT}/drivers/vga/vga.c

    ${MYOS_ROOT}/filesystem/core/fs.c
)

# --------------------------------------------------
# Editor sources
# --------------------------------------------------

file(
    GLOB_RECURSE
    EDITOR_SOURCES
    CONFIGURE_DEPENDS
    ${MYOS_ROOT}/editor/*.c
)

# --------------------------------------------------
# Kernel objects
# --------------------------------------------------

add_library(kernel_objects OBJECT
    ${KERNEL_SOURCES}
    ${EDITOR_SOURCES}
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

add_custom_target(bootloader DEPENDS ${BOOT_BIN})

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

add_custom_target(stage2 DEPENDS ${STAGE2_BIN})

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

add_custom_target(kernel_bin DEPENDS ${KERNEL_BIN})

# --------------------------------------------------
# OS image
# --------------------------------------------------

set(OS_IMAGE ${MYOS_BUILD}/os.bin)

add_custom_command(
    OUTPUT ${OS_IMAGE}

    COMMAND ${CMAKE_COMMAND}
            -DBOOT=${BOOT_BIN}
            -DSTAGE2=${STAGE2_BIN}
            -DKERNEL=${KERNEL_BIN}
            -DOUTPUT=${OS_IMAGE}
            -P ${MYOS_ROOT}/cmake/create_image.cmake

    DEPENDS
        ${BOOT_BIN}
        ${STAGE2_BIN}
        ${KERNEL_BIN}
        ${MYOS_ROOT}/cmake/create_image.cmake

    COMMENT "Creating OS image..."
)

add_custom_target(
    os_image
    ALL
    DEPENDS ${OS_IMAGE}
)

add_dependencies(
    os_image
    bootloader
    stage2
    kernel_bin
)