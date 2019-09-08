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

#include "hal.h"
#include "uart.h"

/*
*  HAL IO Serial Init
*/
uint32_t hal_io_serial_init( void ){
	uart0_init();			
	return HAL_SUCCESS;
}

/*
*  HAL IO Serial Puts
*/
void hal_io_serial_puts( SerialId serial_id, uint8_t* str){
	while(*str)
		hal_io_serial_putc( serial_id, *str++);
}

/*
*  HAL IO Serial Putc
*/
void hal_io_serial_putc( SerialId id, uint8_t c ){
	switch(id){
		case SerialA: uart0_putc(c); break;
		case SerialB: /* Unimplemented*/ break;
	}
}

/*
*  HAL IO Serial Getc
*/
uint8_t hal_io_serial_getc( SerialId id ){
	switch(id){
		case SerialA: return uart0_getc();
		case SerialB: /* Unimplemented*/ return 0;
	}
}
