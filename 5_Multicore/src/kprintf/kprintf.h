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

/* Copyright (C) 2007-2015 Goswin von Brederlow <goswin-v-b@web.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Definition of the family of printf functions.
 */

#ifndef KERNEL_KPRINTF_H
#define KERNEL_KPRINTF_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/cdefs.h>

void kprintf_hex_dump( uint8_t*, uint32_t, uint32_t, uint32_t);

void kprintf(const char *format, ...);
void kprintf_debug(const char *format, ...);

int snprintf(char *buf, size_t size, const char *format, ...);

int vsnprintf(char *buf, size_t size, const char *format, va_list args);

typedef void (*vcprintf_callback_t)(char c, void *state);

void cprintf(vcprintf_callback_t callback, void *state, const char* format,
	     ...);

void vcprintf(vcprintf_callback_t callback, void *state, const char* format,
	      va_list args);

#endif // #ifndef PRINTF_H
