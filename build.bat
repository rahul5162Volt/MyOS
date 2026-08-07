@echo off
echo Building MyOS...

if not exist build mkdir build

nasm -f bin boot\boot.asm -o build\boot.bin
nasm -f bin boot\stage2.asm -o build\stage2.bin

:: Pad Stage2 to exactly 512 bytes
fsutil file seteof build\stage2.bin 512

nasm -f elf32 kernel\kernel_entry.asm -o build\kernel_entry.o

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-c kernel\kernel.c ^
-o build\kernel.o

i686-elf-ld ^
-m elf_i386 ^
-T linker\linker.ld ^
-o build\kernel.elf ^
build\kernel_entry.o ^
build\kernel.o

i686-elf-objcopy ^
-O binary ^
build\kernel.elf ^
build\kernel.bin

:: Pad kernel to a whole number of sectors (temporary: 512 bytes)
fsutil file seteof build\kernel.bin 512

copy /b ^
build\boot.bin+build\stage2.bin+build\kernel.bin ^
build\os.bin >nul

fsutil file seteof build\os.bin 1474560

qemu-system-i386 ^
-drive format=raw,file=build\os.bin

pause