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

AS=aarch64-elf-gcc
CC=aarch64-elf-gcc
LD=aarch64-elf-ld
OBJCOPY=aarch64-elf-objcopy
OBJDUMP=aarch64-elf-objdump
ELF=kernel8.elf
IMAGE=kernel8.img

TARGET_EXEC ?= kernel8.img
SRC_DIRS ?= ./src
BUILD_DIR ?= ./build
OUTPUT ?= ./output

SRCS := $(shell find $(SRC_DIRS) -name *.c -or -name *.S)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS = $(INC_FLAGS) -mcpu=cortex-a53 -O0 -nostdlib -ffreestanding
LDFLAGS = -L/gnu_toolchain/aarch64-elf/lib/ -lc -L/gnu_toolchain/lib/gcc/aarch64-elf/8.3.0/ -lgcc

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -T linker.ld -o $(OUTPUT)/$(ELF)
	$(OBJCOPY) -O binary $(OUTPUT)/$(ELF) $(OUTPUT)/$(IMAGE)
	$(OBJDUMP) -D $(OUTPUT)/$(ELF) > $(OUTPUT)/kernel8.lss
	$(OBJDUMP) -s $(OUTPUT)/$(ELF) > $(OUTPUT)/kernel8.dump

# assembly
$(BUILD_DIR)/%.S.o: %.S
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)


MKDIR_P ?= mkdir -p
