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
    src/uart.c `
    src/main.c `
    -o output/kernel8.img

	& "C:\Users\a01169587\Downloads\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf.tar\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf\bin\aarch64-elf-objdump" -D .\output\kernel8.img | Out-File -filepath output/kernel8.lss -Encoding ASCII
    & "C:\Users\a01169587\Downloads\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf.tar\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf\bin\aarch64-elf-objdump" -s .\output\kernel8.img | Out-File -filepath output/kernel8.dump -Encoding ASCII


& 'C:\Program Files\qemu\qemu-system-aarch64.exe' -M raspi3 -kernel output/kernel8.img -serial null -serial stdio
