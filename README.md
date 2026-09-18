# MyOS

A hobby operating system written from scratch.

---

# Current Stage

**Milestone 11: OS Startup Environment**

The current system successfully boots through the bootloader, initializes the framebuffer, starts the kernel, displays the MyOS startup logo, shows the main menu, and launches the editor.

## Completed Foundation

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
- [x] UI layout system
- [x] UI screen system
- [x] Header
- [x] Status bar
- [x] UI integration tests
- [x] Editor foundation
- [x] Editor cursor
- [x] Editor selection
- [x] Editor navigation
- [x] Editor text editing
- [x] Editor undo/redo
- [x] Editor clipboard
- [x] Keyboard polling
- [x] OS startup module
- [x] Startup logo
- [x] Main menu
- [x] Menu selection
- [x] Editor launch from OS menu

---

# Architecture

```text
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
 |
OS Startup
 |
Main Menu
 |
Applications
```

---

# OS Roadmap

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

---

# Phase 2 — Hardware & Video

## Milestone 5 — Basic Hardware Output

- [x] VGA text output
- [x] Port I/O
- [x] Basic keyboard driver

## Milestone 6 — VBE / Framebuffer

- [x] VBE initialization
- [x] 1024x768 framebuffer
- [x] 32-bit color
- [x] Video information structure
- [x] Framebuffer address
- [x] Pitch / width / height / bpp

## Milestone 7 — Graphics Renderer

- [x] Pixel rendering
- [x] Rectangle rendering
- [x] Screen clearing
- [x] Bitmap font rendering
- [x] Font scaling
- [x] Text layout
- [x] Text alignment

---

# Phase 3 — UI System

## Milestone 8 — UI Foundation

- [x] UI abstraction
- [x] UI backend
- [x] Framebuffer backend
- [x] UI color system
- [x] UI drawing API

## Milestone 9 — UI Components

- [x] Panels
- [x] Windows
- [x] Text
- [x] Buttons
- [x] Layout system
- [x] Screen system
- [x] Header
- [x] Status bar

## Milestone 10 — UI Testing

- [x] Logo test
- [x] Editor test
- [x] Menu test
- [x] Window test
- [x] Text test
- [x] Button test

---

# Phase 4 — OS Startup

## Milestone 11 — OS Startup Environment

- [x] Create OS startup layer
- [x] Startup logo
- [x] Startup transition
- [x] Main menu
- [x] Menu selection
- [x] Editor launch
- [ ] Separate applications from integration tests
- [ ] Application entry-point architecture
- [ ] Application lifecycle
- [ ] Return from applications to OS
- [ ] Main menu navigation

Target architecture:

```text
OS Startup
    |
Main Menu
    |
Applications
    |
Editor
```

---

# Phase 5 — Kernel Architecture

## Milestone 12 — Kernel Subsystems

- [ ] Kernel initialization framework
- [ ] Kernel panic system
- [ ] Kernel logging
- [ ] Kernel configuration
- [ ] Kernel memory layout
- [ ] Hardware abstraction
- [ ] Kernel subsystem organization

Target structure:

```text
kernel/
├── core/
├── memory/
├── process/
├── interrupt/
├── time/
├── device/
└── syscall/
```

---

# Phase 6 — Memory Management

## Milestone 13 — Physical Memory Manager

- [ ] Detect available RAM
- [ ] Memory map
- [ ] Physical page allocator
- [ ] Page allocation
- [ ] Page freeing
- [ ] Reserved memory regions
- [ ] Kernel memory protection

## Milestone 14 — Virtual Memory

- [ ] Paging
- [ ] Page directory
- [ ] Page tables
- [ ] Virtual-to-physical mapping
- [ ] Kernel address space
- [ ] User address space
- [ ] Page faults

---

# Phase 7 — Interrupts & Hardware

## Milestone 15 — Interrupt System

- [ ] IDT
- [ ] Interrupt descriptors
- [ ] CPU exception handlers
- [ ] General Protection Fault
- [ ] Page Fault
- [ ] Double Fault
- [ ] Keyboard IRQ
- [ ] Timer IRQ
- [ ] Interrupt controller

Replace polling-based input with:

```text
Keyboard
   |
IRQ
   |
Keyboard Driver
   |
Input Queue
   |
OS / UI
```

## Milestone 16 — Hardware Abstraction

- [ ] PIC
- [ ] APIC
- [ ] PIT
- [ ] RTC / CMOS
- [ ] PCI
- [ ] Device discovery
- [ ] Generic device interface

---

# Phase 8 — Process & Task System

## Milestone 17 — Processes

- [ ] Process structure
- [ ] Process IDs
- [ ] Address spaces
- [ ] Kernel/user separation
- [ ] Process creation
- [ ] Process termination
- [ ] Process states

## Milestone 18 — Multitasking

- [ ] Context switching
- [ ] Scheduler
- [ ] Timer-driven scheduling
- [ ] Runnable queue
- [ ] Sleeping processes
- [ ] Basic process priorities

Target:

```text
MyOS
├── System
├── Editor
├── Shell
└── Applications
```

---

# Phase 9 — System Calls

## Milestone 19 — System Call Interface

- [ ] Syscall mechanism
- [ ] Process syscalls
- [ ] Memory syscalls
- [ ] File syscalls
- [ ] Console syscalls
- [ ] Input syscalls
- [ ] Time syscalls

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

# Phase 10 — Storage & Filesystem

## Milestone 20 — Disk Driver

- [ ] Disk abstraction
- [ ] ATA / IDE or AHCI
- [ ] Sector read
- [ ] Sector write
- [ ] Disk identification
- [ ] Block device layer

## Milestone 21 — Filesystem

- [ ] Filesystem abstraction
- [ ] File structure
- [ ] Directory structure
- [ ] File creation
- [ ] File deletion
- [ ] File reading
- [ ] File writing
- [ ] Open
- [ ] Close

Initial filesystem hierarchy:

```text
/
├── bin/
├── dev/
├── home/
├── system/
└── tmp/
```

---

# Phase 11 — Shell

## Milestone 22 — Command Shell

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

# Phase 12 — User Applications

## Milestone 23 — Application Framework

- [ ] Application abstraction
- [ ] Application entry point
- [ ] Application lifecycle
- [ ] Application loading
- [ ] Application termination
- [ ] Application isolation

Target structure:

```text
apps/
├── shell/
├── editor/
├── terminal/
├── settings/
└── ...
```

## Milestone 24 — Editor Application

- [x] Text editing foundation
- [x] Cursor
- [x] Selection
- [x] Navigation
- [x] Clipboard
- [x] Undo / redo
- [ ] File loading
- [ ] File saving
- [ ] Application lifecycle
- [ ] Window integration

---

# Phase 13 — GUI

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

Architecture:

```text
Applications
     |
Window Manager
     |
UI
     |
Renderer
     |
Framebuffer
```

---

# Phase 14 — Input

## Milestone 26 — Complete Input System

### Keyboard

- [x] Basic keyboard driver
- [ ] IRQ keyboard
- [ ] Input queue
- [ ] Key events

### Mouse

- [ ] PS/2 mouse
- [ ] Mouse IRQ
- [ ] Mouse cursor
- [ ] Click events
- [ ] Scroll events

Input architecture:

```text
Hardware
   |
Driver
   |
Input Subsystem
   |
Application / UI
```

---

# Phase 15 — Networking

## Milestone 27 — Network Stack

- [ ] NIC driver
- [ ] Ethernet
- [ ] ARP
- [ ] IPv4
- [ ] ICMP
- [ ] UDP
- [ ] TCP
- [ ] DNS
- [ ] DHCP

Target:

```text
Internet
   |
TCP/IP
   |
MyOS
   |
Applications
```

---

# Phase 16 — Security & Isolation

## Milestone 28 — User Mode

- [ ] Ring 3
- [ ] User processes
- [ ] Kernel/user separation
- [ ] Protected memory
- [ ] Syscall boundary

## Milestone 29 — Security

- [ ] Permissions
- [ ] File ownership
- [ ] Process isolation
- [ ] Memory protection
- [ ] Syscall validation

---

# Phase 17 — System Services

## Milestone 30 — OS Services

- [ ] Init / system manager
- [ ] Device manager
- [ ] Process manager
- [ ] Filesystem service
- [ ] Input service
- [ ] Window manager
- [ ] Logging service

---

# Phase 18 — User Experience

## Milestone 31 — Desktop Environment

- [ ] Desktop
- [ ] Taskbar
- [ ] Application launcher
- [ ] Window manager
- [ ] Notifications
- [ ] Settings
- [ ] File manager
- [ ] Terminal

Target:

```text
        MyOS
         |
   +-------------+
   |   Desktop   |
   |             |
   |   Editor    |
   |   Terminal  |
   |   Settings  |
   |   Files     |
   +-------------+
```

---

# Phase 19 — Developer Ecosystem

## Milestone 32 — Native Development

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

# Phase 20 — Advanced Hardware

## Milestone 33 — Modern Hardware

- [ ] ACPI
- [ ] APIC
- [ ] SMP / multiple CPU cores
- [ ] PCIe
- [ ] USB
- [ ] USB HID
- [ ] Audio
- [ ] GPU acceleration

---

# Phase 21 — x86-64

## Milestone 34 — 64-bit MyOS

After the 32-bit architecture is mature:

- [ ] 64-bit bootloader
- [ ] PAE
- [ ] Long mode
- [ ] 64-bit GDT
- [ ] 64-bit paging
- [ ] 64-bit kernel
- [ ] 64-bit syscall ABI
- [ ] 64-bit applications

Target:

```text
32-bit MyOS
     |
Long Mode
     |
64-bit Kernel
     |
64-bit Applications
```

---

# Phase 22 — MyOS 1.0

## Milestone 35 — Production OS

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
│   ├── memory.inc
│   └── vbe.inc
│
├── kernel/
│   ├── kernel.c
│   ├── kernel_entry.asm
│   ├── io/
│   └── video/
│
├── drivers/
│   ├── keyboard/
│   └── vga/
│
├── editor/
│   ├── clipboard/
│   ├── core/
│   ├── cursor/
│   ├── document/
│   ├── edit/
│   ├── input/
│   ├── lines/
│   ├── navigation/
│   ├── render/
│   ├── selection/
│   ├── text/
│   └── undo/
│
├── ui/
│   ├── core/
│   ├── layout/
│   ├── render/
│   ├── screen/
│   ├── text/
│   └── window/
│
├── os/
│   └── startup/
│
├── tests/
│   └── integration/
│       └── ui/
│
├── linker/
├── cmake/
├── CMakeLists.txt
└── build.bat
```

---

# Final Architecture

The long-term architecture is:

```text
                    Applications
                         |
                    System Calls
                         |
              +----------v----------+
              |        Kernel       |
              |                     |
              | Process / Scheduler |
              | Memory Management   |
              | Filesystem          |
              | IPC                 |
              | Security            |
              | Networking          |
              +----------+----------+
                         |
              +----------v----------+
              |   Device Drivers    |
              |                     |
              | Keyboard / Mouse    |
              | Disk / Network      |
              | USB / Display       |
              +----------+----------+
                         |
                    Hardware
```

---

# Current Status

MyOS currently boots successfully in QEMU and enters 32-bit protected mode.

The kernel initializes a VBE 1024x768 32-bit framebuffer and provides a rendering stack consisting of the framebuffer, renderer, font system, and UI backend.

The UI layer supports character-cell rendering, colors, panels, windows, titles, text, buttons, layout, and screen composition.

The OS startup layer now displays the MyOS logo, transitions to a main menu, and launches the Editor through keyboard selection.

The next major architectural task is to separate the production Editor application from the integration-test environment. After that, development moves toward kernel architecture, memory management, and interrupt handling.

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
