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

.section ".boot"
.align 2

.global _boot_entry_point
_boot_entry_point:
    // Halt cores from 1 to 3
    // Only core 0 runs
    //
    //  MPIDR_EL1 (Multiprocessor Affinity Register)
    //    - It's a 64-bit register.
    //    - It "provides an additional PE [processing element] identification mechanism"
    //
    //
    mrs   x0, mpidr_el1
    and   x0, x0, 3
    cbnz  x0, halt            //Only core 0 will make it thru

    ldr   x0, =__stack_end    //Init stack
    mov   sp, x0

    ldr   x4, =__bss_start     // Fill BSS with Zeroes
	ldr   x9, =__bss_end
	mov   w5, 0
bss_next_word:
	cmp   x4, x9
	bge   bss_end
    str   w5, [x4]
    add   x4, x4, 4
	b bss_next_word
bss_end:

    bl      main                 //Jump to main

halt:
    wfe                          //Low power mode
    b halt
