# MyOS

A hobby operating system written from scratch.

## Current Stage

**Milestone 9: Framebuffer UI Foundation**

- [x] Boot Sector
- [x] Disk Loader
- [x] Two-stage bootloader
- [x] Kernel loaded into memory
- [x] A20 enabled
- [x] Global Descriptor Table (GDT)
- [x] Enter 32-bit Protected Mode
- [x] 32-bit kernel entry
- [x] C kernel execution
- [x] VGA text output
- [x] Persistent VGA cursor
- [x] Newline and carriage return handling
- [x] VGA screen clearing
- [x] VGA scrolling
- [x] VBE initialization
- [x] 1024x768 32-bit framebuffer mode
- [x] Framebuffer rendering
- [x] Renderer abstraction
- [x] Basic shape rendering
- [x] Bitmap font rendering
- [x] Font scaling and text layout
- [x] UI backend abstraction
- [x] Framebuffer UI backend
- [x] UI color abstraction
- [x] UI panels
- [x] UI windows
- [x] UI text
- [ ] Keyboard input
- [ ] Memory management
- [ ] Interrupt handling

## Architecture

BIOS
  |
Stage 1
  |
Stage 2
  |
VBE Initialization
  |
Load Kernel
  |
A20 + GDT
  |
32-bit Protected Mode
  |
C Kernel
  |
Framebuffer
  |
Renderer
  |
UI Backend
  |
UI

## Project Structure

- boot/ - Bootloader components
  - boot.asm - Initial boot sector
  - stage2.asm - Second-stage bootloader
  - vbe.asm - VBE initialization
  - disk.asm - Kernel disk loading

- kernel/ - Main kernel code
  - kernel.c - Main kernel entry point
  - kernel_entry.asm - Assembly entry point
  - video/ - Video, framebuffer, renderer, and font systems
  - io/ - Kernel I/O
  - drivers/ - Hardware drivers

- ui/ - User interface system
  - render/ - UI rendering abstraction and framebuffer backend
  - text/ - UI text components
  - layout/ - UI panels and layout components
  - window/ - UI windows
  - screen/ - UI screen composition

- linker/ - Linker script for the kernel
- cmake/ - CMake build configuration
- tests/ - Project tests

## Build System

The project uses a cross-compilation toolchain:

- i686-elf-gcc for C compilation
- nasm for assembly
- ld for linking
- objcopy for binary conversion
- cmake for build configuration
- ninja for builds
- qemu for testing

## Current Status

The system boots successfully in QEMU and enters 32-bit protected mode.

The kernel now initializes a VBE 1024x768 32-bit framebuffer and provides a rendering stack consisting of the framebuffer, renderer, font system, and UI backend.

The UI layer currently supports character-cell rendering, colors, panels, windows, titles, and text. The framebuffer backend replaces the previous VGA text-memory rendering path while keeping the UI architecture separated from the underlying rendering implementation.

The next major areas are input handling, interrupts, and memory management.
