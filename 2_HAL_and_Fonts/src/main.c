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
#include "hal/hal.h"
#include "alice.h"


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

void wait_for_ten_secs(void);

uint32_t zoom_title=2;
uint32_t zoom_text=1;
bool changed=true;

void main(){

    hal_io_serial_init();

    if( hal_video_init() == HAL_FAILED ){
        while(true){
            hal_io_serial_puts( SerialA, "Failed initializing Video. Cannot continue.\n\r" );
            wait_for_ten_secs();
        }
    }

	for(uint32_t i=0; i<600; i++)
		put_pixel_raw( i, 0xFFFFFFFF );

    while(true){
        if(changed){
            hal_video_clear();
            hal_video_puts( "Excerpt from Alice in Wonderland:\n\r\n\r\n\r" , 2, VIDEO_COLOR_GREEN );

            hal_video_puts( title , zoom_title, VIDEO_COLOR_WHITE );
            hal_video_puts( alice , zoom_text, VIDEO_COLOR_WHITE );

            hal_video_puts( "\n\r\n\r(-) Zoom Out, (+) Zoom In", 2, VIDEO_COLOR_GREEN  );
        }
        switch( hal_io_serial_getc(SerialA) ){
            case '+':
                hal_io_serial_puts( SerialA, "Zoom In\n\r" );
                zoom_title++;
                zoom_text++;
                changed=true;
                break;
            case '-':
                hal_io_serial_puts( SerialA, "Zoom Out\n\r" );
                zoom_title--;
                zoom_text--;
                changed=true;
                break;
            default:
                changed=false;
                break;
        }
    }
}

void wait_for_ten_secs(void){
    for(uint32_t i=0; i<10; i++)
        hal_cpu_delay(1000);
}
