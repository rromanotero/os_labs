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
#include "rpi-smartstart.h"
#include "delays.h"
#include "hal.h"

//SVC-related defintions
void (*svc_callback)(void);


/*
*	CPU Init
*
*	Inits CPU cores, sets them to max speed,
*	and provides the caller with CPU details.
*/
void hal_cpu_init( CPUInfo* cpu ){
	//Cores should be initilaized at this point
	//(see SmartStart64.S)

	//Set cores to max speed
	//uint32_t max_speed = ARM_setmaxspeed();
	//
	//   BUG: SD CARD DRIVERS FAIL WHEN SETTING TO MAX SPEED
	//cpu->ARM_setmaxspeed()/1000; //<<---- This line messes with the SD CARD drivers
	cpu->speed_mhz = 0; //0 means unknow

	//Get remaining details
	cpu->name = ((uint8_t*)RPi_CpuIdString());
	cpu->num_cores = RPi_CoresReady;
}


/*
*	Enable All interrupts
*/
void hal_cpu_ints_enable( void ){
	//This enable ALL interrupts
	EnableInterrupts();
}

/*
*	Disable All interrupts
*/
void hal_cpu_ints_disable( void ){
	//This disables ALL interrupts
	DisableInterrupts();
}


/*
*	Start CPU Thread (in a Core number)
*
*		We call CPU thread, not a software thread that is scheduled,
*	but a hardware thread. Each core having the ability to indepedently
*	execute code is a "flow of execution" i.e. a thread.
*
*/
void hal_cpu_thread_start( uint32_t core_num, void(*code)(void) ){
	CoreExecute( core_num, code );
}

/**
*	SVC Start
*
*	Starts SVC calls and registers a callback function. The callback
*	execution of an SVC instruction
*
*	@param callback the function that gets called on supervisor calls
*/
void hal_cpu_svc_start( void(*callback)(void) ){
	svc_callback = callback; //SVC Handler definition is in hal_cpu_asm.s
}

/**
*	CPU Delays
*
*	Busy-waiting delay
*
*	@param delay_in_ms delay in milliseconds
*/
void hal_cpu_delay(uint32_t delay_in_ms){
	delays_wait_microsecs(delay_in_ms*1000);
}
