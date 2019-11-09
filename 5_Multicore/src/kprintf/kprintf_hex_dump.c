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

#include <stdint.h>
#include <stddef.h>
#include "kprintf.h"


#define LINE_LENGTH		20

void kprintf_hex_dump( uint8_t* buffer, uint32_t size, uint32_t marker_pos_a, uint32_t marker_pos_b ){
	int i=0;
	uint32_t curr_pos=0;
	for( i=0; i<(size-LINE_LENGTH); i+=LINE_LENGTH ) {

        //for every line

		//dump as hex
		for(	int j=0; j<LINE_LENGTH; j++ ){
			if( curr_pos >= marker_pos_a && curr_pos <= marker_pos_b )
				kprintf( "!%02x ", buffer[ i+j ] );
			else
				kprintf( "%02x ", buffer[ i+j ] );

			curr_pos++;
		}

		//dump as ascii
		for(	int j=0; j<LINE_LENGTH; j++ ) {
			uint8_t byte = buffer[ i+j ];

			if( byte == '\n' || byte == '\r' )
				continue;

			if( (byte >= 'a' && byte <= 'z') ||
			 		(byte >= 'A' && byte <= 'Z') ||
					(byte >= '0' && byte <= '9')
			  ){
				kprintf( "%c", byte );
			}
			else{
				kprintf( " " );
			}
	    }

		//next line
		kprintf( "\n\r" );
	}

	//print last line
	//dump as hex
	for( int j=i; j<size; j++ ){
		if( curr_pos >= marker_pos_a && curr_pos <= marker_pos_b )
			kprintf( "!%02x ", buffer[ j ] );
		else
			kprintf( "%02x ", buffer[ j ] );
	}

	//dump as ascii
	for( int j=i; j<size; j++ ) {
		uint8_t byte = buffer[ j ];

		if( byte == '\n' || byte == '\r' )
			continue;

		if( (byte >= 'a' && byte <= 'z') ||
				(byte >= 'A' && byte <= 'Z') ||
				(byte >= '0' && byte <= '9')
			){
			kprintf( "%c", byte );
		}
		else{
			kprintf( " " );
		}

	}

	kprintf( "\n\r" );
}
