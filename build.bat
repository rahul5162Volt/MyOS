@echo off
setlocal

echo Building MyOS...
echo.

cmake -S . -B build-cmake -G Ninja
if errorlevel 1 goto failed

cmake --build build-cmake
if errorlevel 1 goto failed

echo.
echo Build successful.
echo Starting QEMU...
echo.

qemu-system-i386 ^
    -drive format=raw,file=build-cmake\os.bin ^
    -d int,cpu_reset,guest_errors ^
    -D qemu-cmake.log ^
    -no-reboot ^
    -no-shutdown

goto end

:failed
echo.
echo Build failed.
pause
exit /b 1

:end