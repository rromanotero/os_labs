@Passed by caller
set GCC_BIN_PATH=%1

@REM COMPILER COMMAND LINE
@echo off
set "cpuflags= -O3 -march=armv8-a+simd -mtune=cortex-a53 -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize"
set "asmflags=-nostdlib -nostartfiles -ffreestanding -fno-asynchronous-unwind-tables -fomit-frame-pointer -Wa,-a>output/list.txt"
set "linkerflags=-Wl,-gc-sections -Wl,--build-id=none -Wl,-Bdynamic -Wl,-Map,output/kernel.map"
set "outflags=-o output/kernel8.elf"
set "libflags=-lc -lm -lgcc"
@echo on
%GCC_BIN_PATH%\aarch64-elf-gcc.exe ^
    %cpuflags% %asmflags% %linkerflags% -Wl,-T,linker.ld ^
    -I ./src ^
    -I ./src/drivers ^
    -I ./src/drivers/delays ^
    -I ./src/drivers/fb ^
    -I ./src/drivers/gpio ^
    -I ./src/drivers/mbox ^
    -I ./src/drivers/sd ^
    -I ./src/drivers/uart ^
    -I ./src/fat ^
    -I ./src/hal ^
    -I ./src/kprintf ^
    -I ./src/smartstart ^
    src/main.c ^
    src/system.c ^
    src/smartstart/SmartStart64.S ^
    src/smartstart/rpi-SmartStart.c ^
    src/drivers/delays/delays.c ^
    src/drivers/fb/fb.c ^
    src/drivers/mbox/mbox.c ^
    src/drivers/sd/sd.c ^
    src/drivers/uart/uart.c ^
    src/fat/fat.c ^
    src/hal/fonts.c ^
    src/hal/hal_cpu.c ^
    src/hal/hal_cpu.S ^
    src/hal/hal_io.c ^
    src/hal/hal_sd_card.c ^
    src/hal/hal_video.c ^
    src/hal/hal_timer.c ^
    src/kprintf/kprintf.c ^
    src/kprintf/kprintf_hex_dump.c ^
    %outflags% %libflags%
@echo off
if %errorlevel% EQU 1 (goto build_fail)

exit /b 0

:build_fail
exit /b 1
