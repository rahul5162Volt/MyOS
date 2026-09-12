# MyOS

A hobby operating system written from scratch.

## Current Stage

**Milestone 8: VGA Scrolling**

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
- [ ] Keyboard input
- [ ] Memory management
- [ ] Interrupt handling

## Architecture

```text
BIOS
  Γåô
Stage 1
  Γåô
Stage 2
  Γåô
Load Kernel
  Γåô
A20 + GDT
  Γåô
32-bit Protected Mode
  Γåô
C Kernel
  Γåô
VGA Text Output
```

## Project Structure

- `boot/` - Bootloader components
  - `boot.asm` - Initial boot sector
  - `stage2.asm` - Protected mode loader
  
- `kernel/` - Main kernel code
  - `kernel.c` - Main kernel entry point
  - `kernel_entry.asm` - Assembly entry point

- `drivers/` - Hardware drivers
  - `vga/` - VGA text output driver
  - `keyboard/` - Keyboard input driver

- `linker/` - Linker script for kernel

## Build System

The project uses cross-compilation toolchain:
- `i686-elf-gcc` for compilation
- `nasm` for assembly
- `ld` for linking
- `objcopy` for binary conversion
- `qemu` for testing

## Current Status

The system can boot and display basic text output on VGA. The kernel currently prints "KERN" to screen and has keyboard input handling capabilities, but lacks full functionality.
