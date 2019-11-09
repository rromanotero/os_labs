/**
*   This file is part of os_labs
*   (https://github.com/rromanotero/os_labs).
*
*   Copyright (c) 2019 Rafael Roman Otero.
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
**/

MEMORY
{
	ram : ORIGIN = 0x00000, LENGTH = 0x4000000 /* 64 MB */
}
__stack_size__ = DEFINED(__stack_size__) ? __stack_size__ : 0x400000; /* 4M */

SECTIONS
{
		. = 0x00000;  /* Does not matter, we're compiling PIC */
		__start = .;

		.text : {
				__text_start = .;
				KEEP(*(.entry_point))
				*(.text)
				__text_end = .;
		} > ram

		.data :
		{
				. = ALIGN(4);
				__data_start = .;
				*(.data)
				__data_end = .;
		} > ram

		.bss (NOLOAD):
		{
			 . = ALIGN(4);
				__bss_start = .;
				*(.bss)
				__bss_end = .;
		} > ram

		.rodata : {
				. = ALIGN(4);
				__rodata_start = .;
				*(.rodata)
				__rodata_end = .;
		} > ram

		.stack (NOLOAD):
      {
          . = ALIGN(16);  /* 64-bit APCS requires 128-bit stack alignment */
          __stack_start = .;
          . = . + __stack_size__;
          __stack_end = .;
      } > ram

}
