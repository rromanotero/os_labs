
#include <stdbool.h>
#include <stdint.h>
#include "rpi-smartstart.h"
#include "hal/hal.h"

static uint32_t systick_diff_to_microsecs( uint64_t, uint64_t );
static uint32_t abs_value( uint32_t v );

/**
*	Timer Init
*
*	Initializes HAL Timer
*
*/
void hal_timer_init(void){
    //At the moment we enable ALL interrupts, since we do
    //not have code for enabling JUST IRQ
	hal_cpu_ints_enable();
}

/**
*	Timer Delay (microsecs)
*
8	Similar to CPU delay, but this delay uses
*	a timer to determine elapsed time.
*
*/
void hal_timer_delay_microsecs( uint64_t microsecs ){
	 volatile uint32_t prev_t = hal_timer_read_count( TimerSysTick );

	 //wait
	 volatile uint32_t curr_t;
	 do{
		 curr_t = hal_timer_read_count( TimerSysTick );
	 }while( systick_diff_to_microsecs( curr_t, prev_t ) < microsecs );
}

static uint32_t abs_value( uint32_t v ){
    return (v > 0)? v : -v;
}

static uint32_t systick_diff_to_microsecs( uint64_t curr_t, uint64_t prev_t ){
    return abs_value(curr_t-prev_t); //Systick counts in microsecs
}


/**
*	Timer Start (interrupt)
*
*	Starts a timer with interrupts
*
*   Timers count in steps  (MAX and length of step depends on timer and platform).
*   Here are some option:
*
*	 - TimerMicroseconds:
*       steps is in microseconds. So, for instance, a parameter of 2000 will
*       make the timer increment every 2 ms.
*
*   - SystemTimer":
*       Not implemented yet
*
*   Every time the timer is incremented the registered callback is called.
*
*	@param ms_steps steps needed to increment the timer by one
*	@param callback the function that will be called on every increment
*/
void hal_timer_start_int( TimerId timer_id, uint32_t steps, void (*callback) (void) ){

    switch(timer_id){
        case TimerMicroseconds:
            //ARM Per Core Generic Timer
            TimerIrqSetup( steps, callback );
            break;
        default:
            break;
    }

	//hal_irq_register_callback( IrqMillisecondTimer, callback );

	//enable interrupts
	hal_cpu_ints_enable();
}

/**
*	Timer Start (poll)
*
*	Starts a timer (NO interrupts)
*
*   Timers count in steps  (MAX and granularity of step depends on timer and platform).
*
*   Here are some examples:
*
*	 - TimerMicroseconds:
*       steps is in microseconds.
*
*   - SystemTimer":
*       Steps is in microseconds
*
*/
void hal_timer_start_poll( TimerId timer_id ){

    switch(timer_id){
        case TimerMicroseconds:
            //Unimplemented
            return;
        case TimerSysTick:
            //It's already ON. Nothing to do.
            return;
        default:
            break;
    }

}

/*
*	 Timer Read count
*
*		Returns the current count on a timer
*		(The systick runs at 1Mhz)
*/
uint64_t hal_timer_read_count( TimerId timer_id ){

    switch(timer_id){
        case TimerMicroseconds:
            return 0; //Unimplemented
            break;
        case TimerSysTick:
            return timer_getTickCount();
        default:
            break;
    }
}
