@echo off
setlocal

echo Building MyOS...

if not exist build mkdir build

set KERNEL_SECTORS=8
set /a KERNEL_BYTES=KERNEL_SECTORS * 512

nasm -f bin boot\boot.asm -o build\boot.bin
if errorlevel 1 goto :error

nasm -D KERNEL_SECTORS=%KERNEL_SECTORS% -f bin boot\stage2.asm -o build\stage2.bin
if errorlevel 1 goto :error

for %%I in (build\stage2.bin) do set STAGE2_SIZE=%%~zI

if %STAGE2_SIZE% GTR 512 (
    echo Stage2 is too large: %STAGE2_SIZE% bytes; limit is 512 bytes.
    goto :error
)

fsutil file seteof build\stage2.bin 512
if errorlevel 1 goto :error

nasm -f elf32 kernel\kernel_entry.asm -o build\kernel_entry.o
if errorlevel 1 goto :error

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-c kernel\kernel.c ^
-o build\kernel.o
if errorlevel 1 goto :error

i686-elf-ld ^
-m elf_i386 ^
-T linker\linker.ld ^
-o build\kernel.elf ^
build\kernel_entry.o ^
build\kernel.o
if errorlevel 1 goto :error

i686-elf-objcopy ^
-O binary ^
build\kernel.elf ^
build\kernel.bin
if errorlevel 1 goto :error

for %%I in (build\kernel.bin) do set KERNEL_SIZE=%%~zI

if %KERNEL_SIZE% GTR %KERNEL_BYTES% (
    echo Kernel is too large: %KERNEL_SIZE% bytes; limit is %KERNEL_BYTES% bytes.
    goto :error
)

fsutil file seteof build\kernel.bin %KERNEL_BYTES%
if errorlevel 1 goto :error

copy /b ^
build\boot.bin+build\stage2.bin+build\kernel.bin ^
build\os.bin >nul
if errorlevel 1 goto :error

fsutil file seteof build\os.bin 1474560
if errorlevel 1 goto :error

qemu-system-i386 ^
-drive format=raw,file=build\os.bin ^
-d int,cpu_reset,guest_errors ^
-D qemu.log ^
-no-reboot ^
-no-shutdown

pause
goto :eof

:error
echo.
echo Build failed.
pause
exit /b 1