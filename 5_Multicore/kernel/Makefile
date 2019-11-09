#
#   This file is part of os_labs
#   (https://github.com/rromanotero/os_labs).
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
OBJCOPY=aarch64-elf-objcopy
OBJDUMP=aarch64-elf-objdump
ELF=kernel8.elf
IMAGE=kernel8.img

TARGET_EXEC ?= kernel8.img
SRC_DIRS ?= ./src
BUILD_DIR ?= ./build
OUTPUT ?= ./output

SRCS := $(shell find $(SRC_DIRS) -name *.c -or -name *.S)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS = $(INC_FLAGS) -O3 -march=armv8-a+simd -mtune=cortex-a53 -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize -nostdlib -nostartfiles -ffreestanding -fno-asynchronous-unwind-tables -fomit-frame-pointer
LDFLAGS = -Wl,-gc-sections

$(BUILD_DIR)/$(TARGET_EXEC): $(SRCS)
	$(CC) $(CFLAGS)  $(LDFLAGS) -Wl,-T,linker.ld src/main.c src/SmartStart64.S src/rpi-SmartStart.c src/kprintf/kprintf.c  -o $(TARGET_EXEC)
	$(OBJCOPY) -O binary $(OUTPUT)/$(ELF) $(OUTPUT)/$(IMAGE)
	$(OBJDUMP) -D $(OUTPUT)/$(ELF) > $(OUTPUT)/kernel8.lss
	$(OBJDUMP) -s $(OUTPUT)/$(ELF) > $(OUTPUT)/kernel8.dump

# assembly
.o: %.S
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)


MKDIR_P ?= mkdir -p
