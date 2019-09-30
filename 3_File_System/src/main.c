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
#include "system.h"
#include "hal.h"
#include "fat.h"
#include "kprintf.h"

void print_n_chars( uint8_t*, uint32_t );

uint8_t buffer[1096];
FATDirectory root_dir;

void main(){

	system_init();


	//List files
	kprintf( "\n\r" );
	kprintf( "\n\r" );

	fat_read_files_in_root_dir( &root_dir );

	for( uint32_t i=0; i<FAT_MAX_DIR_ENTRIES; i++ ){
		if( root_dir.files[i].is_archive || root_dir.files[i].is_directory || root_dir.files[i].is_volume ){
				print_n_chars( root_dir.files[i].name, FAT_MAX_FILENAME_LENGTH );

				kprintf( "   " );
				print_n_chars( root_dir.files[i].ext, FAT_MAX_EXT_LENGTH );

				if(	root_dir.files[i].is_directory ) kprintf( "  (DIR)  " );
				else kprintf( "         " );

				if(	root_dir.files[i].is_system ) kprintf( "  (SYSTEM)  " );
				else kprintf( "            " );

				kprintf( "  %d bytes", root_dir.files[i].size );
				kprintf( "\n\r" );
		}
	}

	//Display Alice
	kprintf( "\n\r" );
	kprintf( "\n\r" );
	kprintf( "\n\r" );

	fat_read_file( "ALICE", buffer, 512 ); 
	kprintf( "%s", buffer );

    while(true);
}


void print_n_chars( uint8_t* str, uint32_t len ){
	while( len-- > 0 )
		kprintf( "%c", *str++ );
}

/*
*     For some reason, GCC's built in memcpy doesn't work on the Physical device
*     (even though it works on QEMU), so until I figure this out,
*     here is a custom copy of memcpy
*/
void *memcpy(void *dest, void *src, size_t n){
	uint8_t *my_dest = (uint8_t *)dest;
	uint8_t *my_src = (uint8_t *)src;

	while (n--) {
		*my_dest++ = *my_src++;
	}

	return dest;
}

/*
*     For some reason, GCC's built in strlen doesn't work on the Physical device
*     (even though it works on QEMU), so until I figure this out,
*     here is a custom copy of memcpy
*
*    From https://svnweb.freebsd.org/
*/
size_t strlen(const char * str)
{
    const char *s;
    for (s = str; *s; ++s) {}
    return(s - str);
}
