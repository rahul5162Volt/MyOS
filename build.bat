@echo off

echo ==========================
echo Building MyOS...
echo ==========================


if not exist build (
    mkdir build
)



REM ---------------------------
REM Bootloader
REM ---------------------------

nasm -f bin boot\boot.asm -o build\boot.bin

if errorlevel 1 goto error



REM ---------------------------
REM Stage 2
REM ---------------------------

nasm -f bin boot\stage2.asm -o build\stage2.bin

if errorlevel 1 goto error



REM ---------------------------
REM Kernel Entry
REM ---------------------------

nasm -f elf32 kernel\kernel_entry.asm -o build\kernel_entry.o

if errorlevel 1 goto error



REM ---------------------------
REM C Kernel
REM ---------------------------

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-c kernel\kernel.c ^
-o build\kernel.o


if errorlevel 1 goto error



REM ---------------------------
REM Link Kernel
REM ---------------------------

i686-elf-ld ^
-m elf_i386 ^
-T linker\linker.ld ^
-o build\kernel.elf ^
build\kernel_entry.o ^
build\kernel.o


if errorlevel 1 goto error



REM ---------------------------
REM ELF to Binary
REM ---------------------------

i686-elf-objcopy ^
-O binary ^
build\kernel.elf ^
build\kernel.bin


if errorlevel 1 goto error



REM ---------------------------
REM Disk Image
REM ---------------------------

copy /b ^
build\boot.bin+build\stage2.bin+build\kernel.bin ^
build\os.bin >nul



REM ---------------------------
REM Run
REM ---------------------------

qemu-system-i386 ^
-drive format=raw,file=build\os.bin


goto end



:error

echo.
echo Build Failed.


:end
pause