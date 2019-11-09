aarch64-elf-gcc \
	-mcpu=cortex-a53 \
	-fpic	 \
	-fpie \
	-ffreestanding \
    -nostdlib \
	-T linker.ld  \
	src/runtime.c \
	src/main.c \
	src/lib/lib.c \
    -o output/shell.elf \
	-O0	\
	-s \
	-lc -lm -lg -lgcc

aarch64-elf-objcopy output/shell.elf -O binary output/shell.bin

aarch64-elf-objdump -D ./output/shell.elf > output/shell.lss
aarch64-elf-objdump -s ./output/shell.elf > output/shell.dump
