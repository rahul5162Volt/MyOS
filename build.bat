@echo off
setlocal

echo Building MyOS...
echo.

if exist build-cmake (
    echo Cleaning previous CMake build...
    rmdir /s /q build-cmake
    if errorlevel 1 goto failed
)

echo.
echo Configuring CMake...
echo.

cmake ^
    -S . ^
    -B build-cmake ^
    -G Ninja ^
    -DCMAKE_TOOLCHAIN_FILE=cmake/i686-elf-toolchain.cmake

if errorlevel 1 goto failed

echo.
echo Building MyOS...
echo.

cmake --build build-cmake
if errorlevel 1 goto failed

echo.
echo ========================================
echo Build successful.
echo ========================================
echo.
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
echo ========================================
echo Build failed.
echo ========================================
echo.

pause
exit /b 1


:end
endlocal