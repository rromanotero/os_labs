
<#
#	 Params
#	 (edit path to GCC and QEMU here)
#>

$GCC_BIN_PATH = "C:\Users\a01169587\Downloads\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf.tar\gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf\bin"
$QEMU_BIN_PATH = "C:\Program Files\qemu"



<#
#	 Build process
#>

Clear-Host;

$ErrorActionPreference = "Stop"

Write-Host "  C L E A N I N G "
Write-Host "=================="

rm ./output/*.img
rm ./output/*.elf
rm ./output/*.lss
rm ./output/*.dump
rm ./output/*.map
rm ./output/*.txt

Write-Host "SUCCESS"

Write-Host "  C O M P I L I N G  "
Write-Host "==================="

set "cpuflags=-Wall -O3 -march=armv8-a+simd -mtune=cortex-a53 -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize"
set "asmflags=-nostdlib -nostartfiles -ffreestanding -fno-asynchronous-unwind-tables -fomit-frame-pointer -Wa,-a>output/list.txt"
set "linkerflags=-Wl,-gc-sections -Wl,--build-id=none -Wl,-Bdynamic -Wl,-Map,output/kernel.map"
set "outflags=-o output/kernel8.elf"
set "libflags=-lc -lm -lgcc"


.\compile.bat $GCC_BIN_PATH

if ($LASTEXITCODE -ne 0)
{
	Write-Host " ***** COMPILING FAILED *****"
	exit 1
}
Write-Host "SUCCESS"

Write-Host "  C R E A T I N G    I M G,  L S S,  etc   "
Write-Host "============================================"

& "$GCC_BIN_PATH\aarch64-elf-objcopy" .\output\kernel8.elf -O binary .\output\kernel8.img
& "$GCC_BIN_PATH\aarch64-elf-objdump" -D .\output\kernel8.elf | Out-File -filepath output/kernel8.lss -Encoding ASCII
& "$GCC_BIN_PATH\aarch64-elf-objdump" -s .\output\kernel8.elf | Out-File -filepath output/kernel8.dump -Encoding ASCII

if ($LASTEXITCODE -ne 0)
{
	Write-Host "CREATING IMG et al FAILED"
	exit 1
}
Write-Host "SUCCESS"


Write-Host "            R U N N I N G   "
Write-Host "====================================="
Write-Host "        PI'S  UART0          "
Write-Host "= = = = = = = = = = = = = = "
& "$QEMU_BIN_PATH\qemu-system-aarch64.exe" `
			-M raspi3 `
			-kernel output/kernel8.img  `
			-drive file=.\sd_card\sd_card_many_files.img,if=sd,format=raw `
			-serial stdio -serial null
