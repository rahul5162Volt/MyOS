@echo off
setlocal

echo ==========================
echo Building MyOS...
echo ==========================

if not exist build (
    mkdir build
)

REM ---------------------------------------
REM Assemble Bootloader
REM ---------------------------------------

nasm -f bin boot\boot.asm -o build\boot.bin
if errorlevel 1 goto :error

REM ---------------------------------------
REM Assemble Kernel Entry
REM ---------------------------------------

nasm -f elf32 kernel\kernel_entry.asm -o build\kernel_entry.o
if errorlevel 1 goto :error

REM ---------------------------------------
REM Compile Kernel C
REM ---------------------------------------

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-c kernel\kernel.c ^
-o build\kernel.o

if errorlevel 1 goto :error

REM ---------------------------------------
REM Link Kernel
REM ---------------------------------------

i686-elf-ld ^
-m elf_i386 ^
-T linker\linker.ld ^
-o build\kernel.elf ^
build\kernel_entry.o ^
build\kernel.o

if errorlevel 1 goto :error

REM ---------------------------------------
REM Convert ELF → Flat Binary
REM ---------------------------------------

i686-elf-objcopy ^
-O binary ^
build\kernel.elf ^
build\kernel.bin

if errorlevel 1 goto :error

REM ---------------------------------------
REM Create Disk Image
REM ---------------------------------------

copy /b build\boot.bin+build\kernel.bin build\os.bin >nul

REM ---------------------------------------
REM Run
REM ---------------------------------------

qemu-system-i386 ^
-drive format=raw,file=build\os.bin

goto :eof

:error
echo.
echo Build Failed.
pause
exit /b 1