@echo off
setlocal

echo Building MyOS...

if not exist build mkdir build

set KERNEL_SECTORS=16
set /a KERNEL_BYTES=KERNEL_SECTORS * 512

nasm -f bin boot\boot.asm -o build\boot.bin
if errorlevel 1 goto failed

nasm -D KERNEL_SECTORS=%KERNEL_SECTORS% -f bin boot\stage2.asm -o build\stage2.bin
if errorlevel 1 goto failed

for %%I in (build\stage2.bin) do set STAGE2_SIZE=%%~zI

if %STAGE2_SIZE% GTR 512 (
    echo Stage2 is too large: %STAGE2_SIZE% bytes; limit is 512 bytes.
    goto failed
)

fsutil file seteof build\stage2.bin 512
if errorlevel 1 goto failed

nasm -f elf32 kernel\kernel_entry.asm -o build\kernel_entry.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-I editor ^
-c kernel\kernel.c ^
-o build\kernel.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-c drivers\vga\vga.c ^
-o build\vga.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-c drivers\keyboard\keyboard.c ^
-o build\keyboard.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-I editor ^
-c editor\editor.c ^
-o build\editor.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-I editor ^
-c editor\editor_text.c ^
-o build\editor_text.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-I editor ^
-c editor\editor_cursor.c ^
-o build\editor_cursor.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-I editor ^
-c editor\editor_navigation.c ^
-o build\editor_navigation.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-I editor ^
-c editor\editor_lines.c ^
-o build\editor_lines.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-I editor ^
-c editor\editor_edit.c ^
-o build\editor_edit.o
if errorlevel 1 goto failed

i686-elf-gcc ^
-m32 ^
-ffreestanding ^
-fno-stack-protector ^
-fno-pie ^
-I drivers ^
-I editor ^
-c editor\editor_render.c ^
-o build\editor_render.o
if errorlevel 1 goto failed

i686-elf-ld ^
-m elf_i386 ^
-T linker\linker.ld ^
-o build\kernel.elf ^
build\kernel_entry.o ^
build\kernel.o ^
build\vga.o ^
build\keyboard.o ^
build\editor.o ^
build\editor_text.o ^
build\editor_cursor.o ^
build\editor_navigation.o ^
build\editor_lines.o ^
build\editor_edit.o ^
build\editor_render.o
if errorlevel 1 goto failed

i686-elf-objcopy ^
-O binary ^
build\kernel.elf ^
build\kernel.bin
if errorlevel 1 goto failed

for %%I in (build\kernel.bin) do set KERNEL_SIZE=%%~zI

if %KERNEL_SIZE% GTR %KERNEL_BYTES% (
    echo Kernel is too large: %KERNEL_SIZE% bytes; limit is %KERNEL_BYTES% bytes.
    goto failed
)

fsutil file seteof build\kernel.bin %KERNEL_BYTES%
if errorlevel 1 goto failed

copy /b ^
build\boot.bin+build\stage2.bin+build\kernel.bin ^
build\os.bin >nul
if errorlevel 1 goto failed

fsutil file seteof build\os.bin 1474560
if errorlevel 1 goto failed

qemu-system-i386 ^
-drive format=raw,file=build\os.bin ^
-d int,cpu_reset,guest_errors ^
-D qemu.log ^
-no-reboot ^
-no-shutdown

pause
goto end

:failed
echo.
echo Build failed.
pause
exit /b 1

:end