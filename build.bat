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

if errorlevel 1 goto :error

REM ---------------------------------------
REM Run MyOS
REM ---------------------------------------

qemu-system-i386 ^
-drive format=raw,file=build\boot.bin

goto :eof

:error
echo.
echo Build Failed.
pause
exit /b 1