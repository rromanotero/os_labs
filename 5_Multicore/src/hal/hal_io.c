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
*  HAL IO Serial Hex Dump (512 BYtes)
*
*  Hex Dumps 512 bytes starting from ptr_to_first_byte
*/
void hal_io_serial_hex_dump_512_bytes( SerialId serial_id, uint8_t* ptr_to_first_byte){
	uart0_dump(ptr_to_first_byte);
}


/*
*  HAL IO Put Hex Dump 64-bits
*
*  Writes a 64-bit hex value to serial_id
*/
void hal_io_serial_puthex_64_bits( SerialId serial_id, uint64_t value){
	uart0_puthex_64_bits(value);
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

	if( c == '\n' )
		uart0_putc( '\r' );
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

/*
*	Non-blocking Getc
*/
uint32_t hal_io_serial_nonblocking_getc( SerialId id, uint8_t* c ){
	switch(id){
		case SerialA: return uart0_nonblocking_getc(c);
		case SerialB: /* Unimplemented*/ return 0;
	}
}
