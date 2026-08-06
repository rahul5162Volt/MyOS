@echo off
setlocal

echo ==========================
echo Building MyOS...
echo ==========================

REM ---------------------------------------
REM Create build directory
REM ---------------------------------------

if not exist build (
    mkdir build
)

REM ---------------------------------------
REM Assemble Bootloader
REM ---------------------------------------

nasm -f bin boot\boot.asm -o build\boot.bin
nasm -f bin kernel\kernel.asm -o build\kernel.bin

if errorlevel 1 goto :error

REM ---------------------------------------
REM Run MyOS
REM ---------------------------------------

copy /b build\boot.bin+build\kernel.bin build\os.bin >nul

qemu-system-i386 ^
-drive format=raw,file=build\os.bin

goto :eof

:error
echo.
echo Build Failed.
pause
exit /b 1