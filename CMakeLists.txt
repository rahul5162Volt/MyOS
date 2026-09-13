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

set(STAGE2_SECTORS 4)
set(KERNEL_SECTORS 32)
set(KERNEL_BYTES 16384)
set(OS_IMAGE_SIZE 1474560)

# --------------------------------------------------
# Include directories
# --------------------------------------------------

include_directories(
    ${MYOS_ROOT}/drivers
    ${MYOS_ROOT}/drivers/vga
    ${MYOS_ROOT}/drivers/keyboard

    ${MYOS_ROOT}/kernel
    ${MYOS_ROOT}/kernel/io

    ${MYOS_ROOT}/filesystem
    ${MYOS_ROOT}/filesystem/core

    ${MYOS_ROOT}/editor
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

    ${MYOS_ROOT}/ui
    ${MYOS_ROOT}/ui/core
    ${MYOS_ROOT}/ui/screen
    ${MYOS_ROOT}/ui/window
    ${MYOS_ROOT}/ui/layout
    ${MYOS_ROOT}/ui/text
    ${MYOS_ROOT}/ui/render
)

# --------------------------------------------------
# Build modules
# --------------------------------------------------

include(${MYOS_ROOT}/cmake/drivers.cmake)
include(${MYOS_ROOT}/cmake/filesystem.cmake)
include(${MYOS_ROOT}/cmake/editor.cmake)
include(${MYOS_ROOT}/cmake/ui.cmake)
include(${MYOS_ROOT}/cmake/kernel.cmake)
include(${MYOS_ROOT}/cmake/boot.cmake)

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