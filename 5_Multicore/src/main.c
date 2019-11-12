#include <stdbool.h>		// C standard needed for bool
#include <stdint.h>			// C standard for uint8_t, uint16_t, uint32_t etc
#include "system.h"
#include "hal.h"
#include "kprintf.h"

#define DIR_LEFT    0
#define DIR_RIGHT   1
#define DIR_SAME    2

#define KEY_LEFT    'a'
#define KEY_RIGHT   'd'

uint32_t abs( uint32_t );
uint64_t secs_to_us( uint32_t );
uint64_t ms_to_us( uint32_t );
uint32_t systick_diff_to_ms( uint64_t, uint64_t );

void thread_1(void){
    while(1){
        hal_timer_delay_microsecs( secs_to_us(5) ); //This is a timer delay
                                                    //All this means is that the "wait time" is not based
                                                    //on number of instructions but on the counter of a timer.
                                                    //So it's more accurate.

        kprintf("Thread 1 in Core 1\n");
    }
}

void thread_2(void){
    uint32_t square_length = 40;
    uint32_t init_x = 3*SYSTEM_SCREEN_WIDTH/2;
    uint32_t init_y = square_length;

    VideoArea square = { .init = {  .x = init_x,
                                    .y = init_y
                                 },
                         .end = {   .x = init_x + square_length,
                                    .y = init_y + square_length
                                }
                        };

    uint8_t key;
    uint32_t direction;
    while(1){
        //was any key pressed?
        // (this will read from POWERSHELL, NOT THE EMULATED SCREEN!)
        if( hal_io_serial_nonblocking_getc( SerialA, &key ) ){
            if( key == KEY_LEFT ) direction = DIR_LEFT;
            else direction = DIR_RIGHT;
        }
        else
            direction = DIR_SAME;

        //delete the old square
        hal_video_put_pixel_area( &square, SYSTEM_SCREEN_BACKGROUND_COLOR );

        //update
        square.init.y++;
        square.end.y++;
        if( direction == DIR_LEFT ){
            square.init.x -= 10;
            square.end.x -= 10;
        }
        else if( direction == DIR_RIGHT ){
            square.init.x += 10;
            square.end.x += 10;
        }

        //draw new square
        hal_video_put_pixel_area( &square, VIDEO_COLOR_RED );

        //delay
        hal_timer_delay_microsecs( ms_to_us(38) );
    }
}

volatile uint32_t tick_happened=0;      //Volatile so the compiler does not optimizes
                                        //thread3's loop.

void thread_3(void){
    //Thread 3 is just working on doing something on every "tick"
    //from the microseconds timer started by main.
     uint32_t prev_t=0, curr_t=0, num_of_ticks=1;

     while(1){
         if( tick_happened  ){
             prev_t = curr_t;
             curr_t = hal_timer_read_count( TimerSysTick );    //SysTick is ARM's System Timer
                                                               //it counts in microsecond steps
             if( num_of_ticks > 1 ){
                    kprintf( "Tick. (count: %d, time since last tick: %d milliseconds)\n",
                              num_of_ticks,
                              systick_diff_to_ms(curr_t, prev_t) );
             }
             else{
                 kprintf( "Tick. (count: %d) \n",
                              num_of_ticks );
             }

             tick_happened = 0;
             num_of_ticks++;
        }
     }
}

void timer_handler (void) {
    //Typically you want to keep interrupt handlers
    //as short as possible (specially no IO in here!)
    //
    //(there's a lot of subtleties with interrupts that
    // it's better to stay away from if possible... SERIOUSLY, THEY'RE EVIL )
    //
    //So we let some thread do what we want to do here instad
    tick_happened = 1;
}


int kernel_main (void) {

    system_init();  //This inits everything (should not be removed)

	hal_cpu_thread_start( 1, thread_1 );   // CPU threads are not the typical threads
	hal_cpu_thread_start( 2, thread_2 );   // from a scheduler. These threads ARE NEVER
	hal_cpu_thread_start( 3, thread_3 );   // PREEMTED, and they run in THEIR OWN CORE
                                           // until completion. THEY'RE ALMIGHTY THREADS!

    hal_timer_start_poll( TimerSysTick );   //SysTick is ARM's System Timer
                                            //It counts in steps of 1 microsecond
                                            //We let it go free.... we'll poll it later
                                            //as a measure of time

	hal_timer_start_int( TimerMicroseconds, secs_to_us(3), timer_handler );  //Tick every 3 secs


	while (1) {
            hal_timer_delay_microsecs( secs_to_us(6) ); //This is a timer delay
                                                        //All this means is that the "wait time" is not based
                                                        //on number of instructions but on the counter of a timer.
                                                        //So it's more accurate.
            kprintf("Main Thread in Core 0\n");
	}

	return 0;
}

uint32_t abs( uint32_t v ){
    return (v > 0)? v : -v;
}

uint64_t ms_to_us( uint32_t ms ){
    return ms*1000;
}

uint64_t secs_to_us( uint32_t us ){
    return us*1000000;
}

uint32_t systick_diff_to_ms( uint64_t curr_t, uint64_t prev_t ){
    return abs(curr_t-prev_t)/1000; //Systick counts in microsecs
}
