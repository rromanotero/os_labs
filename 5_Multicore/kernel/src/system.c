
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
#include "hal.h"
#include "fat.h"
//#include "syscalls.h"
#include "kprintf.h"

void wait_for_ten_secs(void);

#define MAX_INFO_SIZE       100
#define INFO_COLOR          VIDEO_COLOR_GREEN
#define BACKGROUND_COLOR    SYSTEM_SCREEN_BACKGROUND_COLOR


uint8_t info_buf[MAX_INFO_SIZE];

/*
*  System Init
*
*  Initializes ALL HAL modules
*/
void system_init(void){

    //Init Serial
    hal_io_serial_init();
    hal_io_serial_puts( SerialA, "Serial Init [OK]\n\r" );


    //Init Video
    if( hal_video_init() == HAL_SUCCESS ){
            snprintf( info_buf,
                      MAX_INFO_SIZE,
                      "Video Init [OK] \n\r    resolution %d x %d\n\r",
                      SYSTEM_SCREEN_WIDTH,
                      SYSTEM_SCREEN_HEIGHT );

            hal_video_clear(BACKGROUND_COLOR);
            hal_video_puts( info_buf, 1, INFO_COLOR );
            kprintf_debug( info_buf );
    }else{
        while(true){
            kprintf_debug( "Video Init [FAILED]. Cannot continue.\n\r" );
            wait_for_ten_secs();
        }
    }

    //Init CPU
    CPUInfo cpu;
    hal_cpu_init( &cpu );

    snprintf( info_buf,
              MAX_INFO_SIZE,
              "CPU Init [OK] \n\r    CPU: %s \n\r    cores: %d \n\r    speed: %d Mhz\n\r",
              cpu.name,
              cpu.num_cores,
              cpu.speed_mhz );

    hal_video_puts( info_buf, 1, INFO_COLOR );
    kprintf_debug( info_buf );


    //Init SDCard
    hal_cpu_delay(1000);    //Give the SD Card 1 sec to be stable
    if( hal_sd_card_init() == HAL_SUCCESS ){
        hal_video_puts( "SD Card Init [OK]\n\r", 1, INFO_COLOR );
        kprintf_debug( "SD Card Init [OK]\n\r" );
    }else{
        while(true){
            hal_video_puts( "SD Card Init [FAILED]. Cannot continue.\n\r", 1, VIDEO_COLOR_RED );
            kprintf_debug( "SD Card Init [FAILED]. Cannot continue.\n\r" );
            wait_for_ten_secs();
        }
    }

	//Init FIle System
    if( fat_init() == FAT_SUCCESS ){
        hal_video_puts( "File System [OK]\n\r", 1, INFO_COLOR );
        kprintf_debug( "File System [OK]\n\r" );
    }else{
        while(true){
            hal_video_puts( "File System [FAILED]. Cannot continue.\n\r", 1, VIDEO_COLOR_RED );
            kprintf_debug( "File System [FAILED]\n\r" );
            wait_for_ten_secs();
        }
    }


    //Init Timers
    hal_timer_init();
    hal_video_puts( "Timers Init [OK]\n\r", 1, INFO_COLOR );
    kprintf_debug( "Timers Init [OK]\n\r" );

    kprintf( "\n\r" );
}

void wait_for_ten_secs(void){
    for(uint32_t i=0; i<10; i++)
        hal_cpu_delay(1000);
}
