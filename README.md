# MyOS

A hobby operating system written from scratch.

---

# Current Focus

**Kernel development with full OS/QEMU testing**

The bootloader and 32-bit kernel foundation are working. Development is now focused on building the kernel's core subsystems while continuously testing the complete OS in QEMU.

UI, graphics, and hardware/video functionality remain in the source tree for testing and development, but they are **not counted as completed kernel milestones**.

## Kernel Development Progress

- [x] Boot sector
- [x] Two-stage bootloader
- [x] LBA disk loading
- [x] Kernel loaded at `0x10000`
- [x] A20 enabled
- [x] GDT
- [x] 32-bit protected mode
- [x] 32-bit kernel entry
- [x] C kernel execution
- [x] Kernel linking
- [x] Kernel status foundation
- [x] Kernel panic foundation
- [x] BIOS E820 memory-map detection
- [x] Kernel-end linker symbol
- [x] Kernel memory boundary alignment
- [x] Initial bump allocator
- [x] Basic page allocation
- [ ] Proper physical page-frame allocator
- [ ] Page freeing
- [ ] Reserved-memory tracking
- [ ] Kernel heap
- [ ] Interrupt / exception infrastructure
- [ ] Timer
- [ ] Interrupt-driven keyboard
- [ ] Process / task foundation
- [ ] Virtual memory
- [ ] System calls
- [ ] User/kernel isolation

---

# Development Rule

The project is currently being developed **kernel-first**.

Every kernel subsystem is developed and tested through the complete boot path:

```text
Bootloader
    |
32-bit Protected Mode
    |
C Kernel
    |
Kernel Subsystem
    |
OS Environment
    |
QEMU Test
```

Existing UI, graphics, editor, and OS-startup code can be used as the test environment, but their functionality does not advance the kernel roadmap.

---

# Architecture

Current development architecture:

```text
BIOS
 |
Stage 1
 |
Stage 2
 |
A20 + GDT
 |
32-bit Protected Mode
 |
C Kernel
 |
+----------------------+
| Kernel               |
|                      |
| Memory               |
| Interrupts           |
| Timer                |
| Processes            |
| Virtual Memory       |
| Syscalls             |
+----------------------+
 |
OS Test Environment
 |
QEMU
```

Long-term architecture:

```text
Applications
     |
System Calls
     |
+-----------------------------+
|           Kernel            |
|                             |
| Process / Scheduler         |
| Memory Management           |
| Virtual Memory              |
| Filesystem                  |
| IPC                         |
| Security                    |
| Networking                  |
+-----------------------------+
     |
Device Drivers
     |
Hardware
```

---

# Roadmap

## Phase 0 — Development Foundation

### Milestone 0 — Toolchain

- [x] NASM
- [x] i686-elf GCC
- [x] CMake
- [x] Ninja
- [x] Git
- [x] QEMU
- [x] Automated build script

---

# Phase 1 — Boot System

## Milestone 1 — Boot Sector

- [x] BIOS boot sector
- [x] `0x7C00` entry point
- [x] Boot signature
- [x] Preserve boot drive
- [x] Load Stage 2

## Milestone 2 — Two-Stage Bootloader

- [x] Stage 1
- [x] Stage 2 at `0x8000`
- [x] BIOS disk access
- [x] LBA disk loading
- [x] Kernel loading at `0x10000`

## Milestone 3 — Protected Mode

- [x] A20
- [x] GDT
- [x] Code segment
- [x] Data segment
- [x] Protected-mode transition
- [x] 32-bit stack
- [x] Jump to kernel

## Milestone 4 — C Kernel

- [x] Kernel entry assembly
- [x] `kernel_main()`
- [x] C kernel foundation
- [x] Kernel linking
- [x] Kernel status system
- [x] Kernel panic foundation

---

# Phase 2 — Kernel Architecture

## Milestone 5 — Kernel Core

- [x] Kernel initialization path
- [x] Kernel status system
- [x] Kernel panic system
- [ ] Kernel logging
- [ ] Kernel configuration
- [ ] Kernel subsystem registration
- [ ] Kernel-wide initialization ordering

Target structure:

```text
kernel/
├── kernel.c
├── kernel.h
├── kernel_panic.c
├── kernel_panic.h
├── kernel_status.h
└── memory/
```

---

## Milestone 6 — Physical Memory Management

- [x] BIOS E820 memory-map detection
- [x] Memory-map structure
- [x] Kernel-end linker symbol
- [x] Kernel memory boundary alignment
- [x] Initial usable-region detection
- [x] Initial bump allocation
- [x] Basic page allocation
- [ ] Page-frame bitmap
- [ ] Proper physical page allocator
- [ ] Page freeing
- [ ] Reserved-memory tracking
- [ ] Kernel memory protection

Current memory boundary:

```text
Kernel load address : 0x10000
Kernel end          : 0x1B034
Aligned free start  : 0x1C000
```

---

## Milestone 7 — Kernel Heap

- [ ] Heap initialization
- [ ] Heap region management
- [ ] Small allocations
- [ ] Free blocks
- [ ] Block coalescing
- [ ] Heap integrity checks
- [ ] Allocation failure handling

---

## Milestone 8 — Interrupt & Exception Foundation

- [ ] IDT
- [ ] Interrupt descriptors
- [ ] CPU exception entry
- [ ] General Protection Fault
- [ ] Page Fault
- [ ] Double Fault
- [ ] Common interrupt handler
- [ ] Interrupt controller setup

---

## Milestone 9 — Timer

- [ ] PIT initialization
- [ ] Timer IRQ
- [ ] Tick counter
- [ ] Timekeeping
- [ ] Timer abstraction

---

## Milestone 10 — Keyboard Interrupts

- [ ] Keyboard IRQ
- [ ] Interrupt-driven keyboard driver
- [ ] Input queue
- [ ] Key events
- [ ] Replace polling-based application input

Target:

```text
Keyboard
   |
IRQ
   |
Keyboard Driver
   |
Input Queue
   |
OS / Applications
```

---

## Milestone 11 — Process & Task Foundation

- [ ] Task structure
- [ ] Process structure
- [ ] Process IDs
- [ ] Context storage
- [ ] Context switching
- [ ] Scheduler foundation
- [ ] Process states
- [ ] Process creation
- [ ] Process termination

---

## Milestone 12 — Virtual Memory

- [ ] Paging
- [ ] Page directory
- [ ] Page tables
- [ ] Virtual-to-physical mapping
- [ ] Kernel address space
- [ ] Page faults
- [ ] User address space

---

## Milestone 13 — System Calls

- [ ] Syscall mechanism
- [ ] Process syscalls
- [ ] Memory syscalls
- [ ] Console syscalls
- [ ] Input syscalls
- [ ] Time syscalls
- [ ] File syscalls

Architecture:

```text
User Application
       |
   System Call
       |
     Kernel
       |
    Hardware
```

---

## Milestone 14 — User / Kernel Isolation

- [ ] Ring 3
- [ ] User processes
- [ ] Kernel/user separation
- [ ] Protected memory
- [ ] Syscall boundary
- [ ] Process isolation

---

# Phase 3 — Hardware & Drivers

These components are important for the OS, but they are **not counted as completed kernel functionality while the project is in kernel-first development**.

## Milestone 15 — Hardware Abstraction

- [ ] Port I/O abstraction
- [ ] Device interface
- [ ] Device discovery
- [ ] PIC
- [ ] APIC
- [ ] PIT
- [ ] RTC / CMOS
- [ ] PCI

## Milestone 16 — Display & Video

- [ ] VBE initialization
- [ ] Framebuffer
- [ ] Renderer
- [ ] Font system
- [ ] Video abstraction

## Milestone 17 — Input Hardware

- [ ] Keyboard driver
- [ ] Mouse driver
- [ ] Input device abstraction

---

# Phase 4 — UI & Applications

UI and application functionality remains available as the OS test environment, but it is intentionally **unchecked in the kernel roadmap** until the underlying kernel architecture is mature.

## Milestone 18 — UI System

- [ ] UI abstraction
- [ ] UI backend
- [ ] Framebuffer backend
- [ ] UI color system
- [ ] UI drawing API
- [ ] Panels
- [ ] Windows
- [ ] Text
- [ ] Layout system
- [ ] Screen system

## Milestone 19 — OS Startup

- [ ] Startup layer
- [ ] Startup logo
- [ ] Main menu
- [ ] Menu navigation
- [ ] Application launch

## Milestone 20 — Application Framework

- [ ] Application abstraction
- [ ] Application entry point
- [ ] Application lifecycle
- [ ] Application loading
- [ ] Application termination
- [ ] Application isolation

## Milestone 21 — Editor

- [ ] Text editing foundation
- [ ] Cursor
- [ ] Selection
- [ ] Navigation
- [ ] Clipboard
- [ ] Undo / redo
- [ ] File loading
- [ ] File saving
- [ ] Window integration

---

# Phase 5 — Storage

## Milestone 22 — Disk Driver

- [ ] Disk abstraction
- [ ] ATA / IDE or AHCI
- [ ] Sector read
- [ ] Sector write
- [ ] Disk identification
- [ ] Block device layer

## Milestone 23 — Filesystem

- [ ] Filesystem abstraction
- [ ] File structure
- [ ] Directory structure
- [ ] File creation
- [ ] File deletion
- [ ] File reading
- [ ] File writing
- [ ] Open
- [ ] Close

---

# Phase 6 — Shell

## Milestone 24 — Command Shell

Create:

```text
MyOS Shell
>
```

Initial commands:

- [ ] `help`
- [ ] `clear`
- [ ] `echo`
- [ ] `ls`
- [ ] `cd`
- [ ] `cat`
- [ ] `mkdir`
- [ ] `touch`
- [ ] `rm`
- [ ] `pwd`
- [ ] `time`
- [ ] `mem`
- [ ] `ps`

---

# Phase 7 — GUI

## Milestone 25 — Window Manager

- [ ] Window objects
- [ ] Window stacking
- [ ] Window focus
- [ ] Active window
- [ ] Mouse cursor
- [ ] Window movement
- [ ] Window resizing
- [ ] Minimize
- [ ] Maximize
- [ ] Close

---

# Phase 8 — Networking

## Milestone 26 — Network Stack

- [ ] NIC driver
- [ ] Ethernet
- [ ] ARP
- [ ] IPv4
- [ ] ICMP
- [ ] UDP
- [ ] TCP
- [ ] DNS
- [ ] DHCP

---

# Phase 9 — Security & System Services

## Milestone 27 — Security

- [ ] Permissions
- [ ] File ownership
- [ ] Process isolation
- [ ] Memory protection
- [ ] Syscall validation

## Milestone 28 — OS Services

- [ ] Init / system manager
- [ ] Device manager
- [ ] Process manager
- [ ] Filesystem service
- [ ] Input service
- [ ] Window manager
- [ ] Logging service

---

# Phase 10 — Developer Ecosystem

## Milestone 29 — Native Development

- [ ] Standard C library
- [ ] C runtime
- [ ] System headers
- [ ] Static libraries
- [ ] Executable format
- [ ] Application loader
- [ ] Native compiler/toolchain
- [ ] Debugging support

Long-term goal:

> Develop MyOS applications directly from MyOS.

---

# Phase 11 — Advanced Hardware

## Milestone 30 — Modern Hardware

- [ ] ACPI
- [ ] SMP / multiple CPU cores
- [ ] PCIe
- [ ] USB
- [ ] USB HID
- [ ] Audio
- [ ] GPU acceleration

---

# Phase 12 — x86-64

## Milestone 31 — 64-bit MyOS

After the 32-bit architecture is mature:

- [ ] 64-bit bootloader
- [ ] PAE
- [ ] Long mode
- [ ] 64-bit GDT
- [ ] 64-bit paging
- [ ] 64-bit kernel
- [ ] 64-bit syscall ABI
- [ ] 64-bit applications

---

# Phase 13 — MyOS 1.0

## Milestone 32 — Production OS

- [ ] Stable boot
- [ ] Stable kernel
- [ ] Memory management
- [ ] Interrupt system
- [ ] Processes
- [ ] Multitasking
- [ ] Filesystem
- [ ] Shell
- [ ] GUI
- [ ] Applications
- [ ] Networking
- [ ] User accounts
- [ ] Security
- [ ] Installer
- [ ] Recovery environment
- [ ] Documentation
- [ ] Release system

---

# Project Structure

```text
MyOS/
├── boot/
│   ├── boot.asm
│   ├── stage2.asm
│   ├── vbe.asm
│   ├── disk.asm
│   ├── memory_map.asm
│   ├── memory.inc
│   └── vbe.inc
│
├── kernel/
│   ├── kernel.c
│   ├── kernel.h
│   ├── kernel_entry.asm
│   ├── kernel_panic.c
│   ├── kernel_panic.h
│   ├── kernel_status.h
│   └── memory/
│       ├── memory.c
│       ├── memory.h
│       └── memory_map.h
│
├── hardware/
├── graphics/
├── drivers/
├── ui/
├── os/
├── apps/
├── editor/
├── tests/
├── linker/
├── cmake/
├── CMakeLists.txt
└── build.bat
```

---

# Current Status

MyOS boots successfully in QEMU through the bootloader and into the 32-bit C kernel.

The kernel now has:

- Kernel initialization
- Kernel status handling
- Kernel panic foundation
- BIOS E820 memory-map detection
- Kernel-end linker boundary
- Page-aligned kernel memory boundary
- Initial bump allocator
- Basic page allocation

The OS, graphics, UI, and editor code are retained as the current testing environment.

**Current development target: Physical Memory Manager.**

The next kernel task is to replace the initial bump allocator with a proper physical page-frame allocator that can track individual physical pages, reserve kernel/boot memory, and later support page freeing.

---

# Build

The project uses a cross-compilation toolchain:

- i686-elf-gcc for C compilation
- NASM for assembly
- ld for linking
- objcopy for binary conversion
- CMake for build configuration
- Ninja for builds
- QEMU for testing

Build the OS with:

```powershell
.\build.bat
```
