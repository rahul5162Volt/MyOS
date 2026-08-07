@echo off

echo Building MyOS...


if not exist build mkdir build



nasm -f bin boot\boot.asm -o build\boot.bin

if errorlevel 1 goto fail



nasm -f bin boot\stage2.asm -o build\stage2.bin

if errorlevel 1 goto fail



nasm -f elf32 kernel\kernel_entry.asm -o build\kernel_entry.o

if errorlevel 1 goto fail



i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-c kernel\kernel.c ^
-o build\kernel.o


if errorlevel 1 goto fail



i686-elf-ld ^
-m elf_i386 ^
-T linker\linker.ld ^
-o build\kernel.elf ^
build\kernel_entry.o ^
build\kernel.o



if errorlevel 1 goto fail



i686-elf-objcopy ^
-O binary ^
build\kernel.elf ^
build\kernel.bin



if errorlevel 1 goto fail



copy /b ^
build\boot.bin+build\stage2.bin+build\kernel.bin ^
build\os.bin >nul



qemu-system-i386 ^
-drive format=raw,file=build\os.bin



goto end



:fail

echo Build Failed



:end

pause