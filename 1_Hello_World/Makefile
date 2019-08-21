#
#   This file is part of computer_architecture_labs
#   (https://github.com/rromanotero/computer_architecture_labs).
#
#   Copyright (c) 2019 Rafael Roman Otero.
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

CC=aarch64-elf-gcc
LD=aarch64-elf-ld
OBJCOPY=aarch64-elf-objcopy
OBJDUMP=aarch64-elf-objdump
ELF=kernel8.elf
IMAGE=kernel8.img

CFLAGS = -mcpu=cortex-a53 -O0 -ffreestanding -nostdlib -nostartfiles

OUTPUT := output
SRC_C := $(wildcard src/*.c)
SRC_S := $(wildcard src/*.s)
OBJS_C := $(SRC_C:c=o)
OBJS_S := $(SRC_S:s=o)

all: $(OUTPUT)/$(IMAGE)

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)/$(IMAGE): $(OBJS_S) $(OBJS_C)
	$(LD) -nostdlib -nostartfiles $(OBJS_S) $(OBJS_C) -T linker.ld -o $(OUTPUT)/$(ELF)
	$(OBJCOPY) -O binary $(OUTPUT)/$(ELF) $(OUTPUT)/$(IMAGE)
	$(OBJDUMP) -D $(OUTPUT)/$(ELF) > $(OUTPUT)/kernel8.lss
	$(OBJDUMP) -s $(OUTPUT)/$(ELF) > $(OUTPUT)/kernel8.dump

clean:
	rm -r src/*.o $(OUTPUT)/*.lss $(OUTPUT)/*.dump $(OUTPUT)/*.elf >/dev/null 2>/dev/null || true
