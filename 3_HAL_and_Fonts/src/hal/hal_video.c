
#include <stdint.h>
#include <stdbool.h>
#include "hal.h"
#include "fonts.h"
#include "fb.h"

#define NULL 0

static inline void put_pixel_raw( uint32_t, uint32_t );

static uint32_t* fb; //Framebuffer pointer

/*
*  HAL Video Init
*/
uint32_t hal_video_init( void ){
    if( (fb=fb_init()) == NULL ){       //Init framebuffer
        return HAL_FAILED;
    }
    fonts_init();

    return HAL_SUCCESS;

}


/*
*  HAL Video Puts
*
*/
void hal_video_puts( uint8_t* string, uint32_t size, VideoColor color ){

}

/*
*  HAL Video Putc
*
*/
void hal_video_putc( uint8_t c, uint32_t size, VideoColor color  ){


}


/*
*  HAL Video Putc XY
*
*/
void hal_video_putc_x_y( uint32_t x, uint32_t y, uint8_t c, uint32_t size, VideoColor color  ){

}


/*
*  HAL Video Clear
*/
void hal_video_clear( void ){

}



///////////////////////////////
/////// DRIVER INTERFACE
//////////////////////////////
static inline void put_pixel_raw( uint32_t raw_pos, uint32_t color ){
    *(fb + raw_pos) = color; //<<<-- Note that addition is pointer arithmetic!
}
