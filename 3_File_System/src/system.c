
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
#include "hal/hal.h"
#include "fat/fat.h"
#include "kprintf/kprintf.h"

void wait_for_ten_secs(void);

/*
*  System Init
*
*  Initializes ALL HAL modules
*/
void system_init(void){

    //Init Serial
    hal_io_serial_init();
    hal_io_serial_puts( SerialA, "Serial Initialize [OK]\n\r" );


    //Init Video
    if( hal_video_init() == HAL_SUCCESS ){
            hal_io_serial_puts( SerialA, "Video Initialize [OK]\n\r" );
            hal_video_puts( "Video Initialize [OK]\n\r", 1, VIDEO_COLOR_GREEN );
    }else{
        while(true){
            hal_io_serial_puts( SerialA, "Video Initialize [FAILED]. Cannot continue.\n\r" );
            wait_for_ten_secs();
        }
    }

    //Init SDCard
    if( hal_sd_card_init() == HAL_SUCCESS ){
        hal_video_puts( "SD Card Initialize [OK]\n\r", 1, VIDEO_COLOR_GREEN );
        hal_io_serial_puts( SerialA, "SD Card Initialize [OK]\n\r" );
    }else{
        while(true){
            hal_io_serial_puts( SerialA, "SD Card Initialize [FAILED]. Cannot continue.\n\r" );
            hal_video_puts( "SD Card Initialize [FAILED]. Cannot continue.\n\r", 1, VIDEO_COLOR_RED );
            wait_for_ten_secs();
        }
    }

	//Init FIle System
    if( fat_init() == FAT_SUCCESS ){
        hal_video_puts( "File System [OK]", 1, VIDEO_COLOR_GREEN );
        hal_io_serial_puts( SerialA, "\n\rFile System [OK]" );
    }else{
        while(true){
            hal_video_puts( "File System [FAILED]. Cannot continue.\n\r", 1, VIDEO_COLOR_RED );
            hal_io_serial_puts( SerialA, "\n\rFile System [FAILED]" );
            wait_for_ten_secs();
        }
    }

	kprintf( "\n\r" );

}

void wait_for_ten_secs(void){
    for(uint32_t i=0; i<10; i++)
        hal_cpu_delay(1000);
}
