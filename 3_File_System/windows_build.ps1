Clear-Host;

$exec=$args[0]
$ErrorActionPreference = "Stop"

Write-Host "Building..."

rm ./output/*.img
rm ./output/*.lss
rm ./output/*.dump

& "C:\Users\a01169587\Downloads\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf.tar\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf\bin\aarch64-elf-gcc.exe" `
	-mcpu=cortex-a53 `
    -O0 `
    -ffreestanding `
    -nostdlib `
	-T linker.ld  `
	src/boot.s `
    src/main.c `
	src/system.c `
	src/hal/fonts.c `
	src/hal/hal_cpu.c `
	src/hal/hal_io.c `
	src/hal/hal_video.c `
	src/drivers/delays/delays.c `
	src/drivers/fb/fb.c `
	src/drivers/mbox/mbox.c `
	src/drivers/uart/uart.c `
	src/kprintf/kprintf_hex_dump.c `
	src/kprintf/kprintf.c `
	src/fat/fat.c `
	src/drivers/sd/sd.c `
	src/hal/hal_sd_card.c `
    -o output/kernel8.img

	& "C:\Users\a01169587\Downloads\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf.tar\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf\bin\aarch64-elf-objdump" -D .\output\kernel8.img | Out-File -filepath output/kernel8.lss -Encoding ASCII
    & "C:\Users\a01169587\Downloads\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf.tar\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf\bin\aarch64-elf-objdump" -s .\output\kernel8.img | Out-File -filepath output/kernel8.dump -Encoding ASCII


& 'C:\Program Files\qemu\qemu-system-aarch64.exe' -M raspi3 -kernel output/kernel8.img -drive file=.\3_File_System\sd_card\sd_card.img,if=sd,format=raw -serial null -serial stdio
