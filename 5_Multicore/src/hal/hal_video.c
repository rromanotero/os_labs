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
#include <stdbool.h>
#include "system.h"
#include "hal.h"
#include "fonts.h"
#include "fb.h"


void _hal_video_put_byte_raw(uint32_t raw_linear_position, uint8_t);

#define X_ORIGIN 	VIDEO_CHARACTER_WIDTH
#define Y_ORIGIN    VIDEO_CHARACTER_HEIGHT*3
uint32_t curr_x=X_ORIGIN;
uint32_t curr_y=Y_ORIGIN;

#define NULL 0

static inline void put_pixel_raw( uint32_t raw_pos, uint32_t color );
static inline uint32_t x_y_to_raw(uint32_t x, uint32_t y);
static void draw_character_raw( uint32_t x, uint32_t y, VideoFont* c, uint32_t size, VideoColor color );
static int32_t abs(int32_t v);
static void wait_for_key();

uint32_t* fb; //Framebuffer pointer

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
*  HAL IO Video Draw Image
*/
void hal_io_video_draw_image( uint8_t* buffer, uint32_t width, uint32_t height ){

	//   ---   CURRENTLY NOT WORKING ---
	//   THIS NEEDS WORK. I UNDERSTIMATED IT. I NEED TO GO NOW,
	//   SO I'LL JUST LEAVE IT AS IT'S NOW.
	//   SEE HERE:
	//        https://engineering.purdue.edu/ece264/16au/hw/HW13
	//
    #define TOP_MARGIN 10
	curr_x = 0;
	curr_y += (height + TOP_MARGIN);
	for(uint32_t rgb_i=0x36; rgb_i < width*height*3 + 0x36; rgb_i+=3){

			uint8_t blue =  ((uint8_t)buffer[rgb_i+0]);
			uint8_t green = ((uint8_t)buffer[rgb_i+1]);
			uint8_t red =  ((uint8_t)buffer[rgb_i+2]);
            uint8_t alpha =  0xFF;

            uint32_t rgba = alpha<<24 | blue<<16 | green<<8 | red;

            //remove padding???
            //
            //I feel this will remove all black pizel, but
            //I guess i"ll find out in the future
            if( rgba!=0xFF000000 )
                put_pixel_raw( x_y_to_raw(curr_x,curr_y), rgba );

			 if( curr_x >= width  ){
				 curr_x = 0;
				 curr_y -= 1;
		 	 }
             else
                 curr_x += 1;
		}

		curr_x = X_ORIGIN;
		curr_y += height;
}


/*
*  HAL IO Video Puts
*
*/
void hal_video_puts( uint8_t* string, uint32_t size, VideoColor color ){
		while(*string)
			hal_video_putc( *string++, size, color );
}

/*
*  HAL IO Video Putc
*
*/
uint8_t* continue_msg = "( Press any key to continue )";
#define CONTINUE_MSG_CHARACTER_SIZE 2
#define CONTINUE_MSG_HEIGHT (VIDEO_CHARACTER_HEIGHT*CONTINUE_MSG_CHARACTER_SIZE+VIDEO_CHARACTER_VERTICAL_SPACE*CONTINUE_MSG_CHARACTER_SIZE )
#define CONTINUE_MSG_WIDTH  340
void hal_video_putc( uint8_t c, uint32_t size, VideoColor color  ){

	if( c == '\n' ){

			//Is there space for a new line?
			if(  curr_y >= VIDEO_MAX_Y - VIDEO_CHARACTER_HEIGHT*size - VIDEO_CHARACTER_VERTICAL_SPACE*size  - CONTINUE_MSG_HEIGHT - 10){
				//No.

				//Wait for user to hit Enter
                wait_for_key();

				//Clear screen and go to origin
				hal_video_clear(SYSTEM_SCREEN_BACKGROUND_COLOR);

				return;
			}

			//Go new line
			curr_y = ( curr_y
							+ VIDEO_CHARACTER_HEIGHT*size
							+ VIDEO_CHARACTER_VERTICAL_SPACE );
            //carriage return
			curr_x = X_ORIGIN;

			return;
	}
	else if( c == '\r' ){
			//carriage return
			curr_x = X_ORIGIN;
			return;
	}
	else{

			//Will the charatacer fit in the current line?
			if(  curr_x >= VIDEO_MAX_X - VIDEO_CHARACTER_WIDTH*size - VIDEO_CHARACTER_HORIZONTAL_SPACE ){
				//No. Go next line.
				hal_video_putc( '\r', size, color );
				hal_video_putc( '\n', size, color );
			}

			//Write the character
			hal_video_putc_x_y( curr_x, curr_y, c, size, color );

			//Move X cursor
			curr_x = ( curr_x
							+ VIDEO_CHARACTER_WIDTH*size
							+ VIDEO_CHARACTER_HORIZONTAL_SPACE );
	}

}

static void wait_for_key(){
    //print msg
    uint8_t* msg = continue_msg;
    uint32_t x = VIDEO_MAX_X - CONTINUE_MSG_WIDTH;
    uint32_t y = VIDEO_MAX_Y - CONTINUE_MSG_HEIGHT;
    while(*msg){
        hal_video_putc_x_y( x, y, *msg, CONTINUE_MSG_CHARACTER_SIZE, VIDEO_COLOR_RED );
        x += VIDEO_CHARACTER_WIDTH*CONTINUE_MSG_CHARACTER_SIZE + VIDEO_CHARACTER_HORIZONTAL_SPACE;
        msg++;
    }
    //wait for Key
    hal_io_serial_getc( SerialA );
}

/*
*  HAL IO Video Putc XY
*
*/
void hal_video_putc_x_y( uint32_t x, uint32_t y, uint8_t c, uint32_t size, VideoColor color  ){
	draw_character_raw(x, y, fonts_char_to_font(c), size, color );
}

static void draw_character_raw( uint32_t x, uint32_t y, VideoFont* c, uint32_t size, VideoColor color ){

	//Draw as per specs
	VideoXY init, end;

	for( int i=0; i<c->num_lines; i++ ){
			//For all lines

			//Set up (x0,y0)*size
			init.x 	= x + c->lines[i].init.x * size;
			init.y 	= y + c->lines[i].init.y * size;

			//Set up (x1,y1)*size
			end.x 	= x + c->lines[i].end.x * size;
			end.y 	= y + c->lines[i].end.y * size;

			hal_video_line( &init, &end, color );
	}

}


/*
*  HAL IO Line
*
*  It used Brasenham's Line Algorithm (Developed at IBM in 1962!).
*
* Actual code from here:
*       https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
*
*/
void hal_video_line( VideoXY* init, VideoXY* end, VideoColor color ){
	int32_t x0= init->x;
	int32_t y0= init->y;
	int32_t x1= end->x;
	int32_t y1= end->y;

	int32_t dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int32_t dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int32_t err = (dx>dy ? dx : -dy)/2, e2;

	VideoXY pos, pos_next;

	for(;;){
		pos.x = x0;
		pos.y = y0;

		hal_video_put_pixel( &pos, color);
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

static int32_t abs(int32_t v){
		if(v<0) return v*(-1);
		else return v;
}


void hal_video_put_pixel_area( VideoArea* area, VideoColor color ){

    //line by line
    for(uint32_t y = area->init.y; y < area->end.y; y++){
        for( uint32_t x=area->init.x; x<area->end.x; x++){
            put_pixel_raw( x_y_to_raw(x,y), color );
        }
    }

}

void hal_video_put_pixel( VideoXY* pos, VideoColor color ){
    put_pixel_raw( x_y_to_raw(pos->x,pos->y), color );
}

void hal_video_put_double_pixel( VideoXY* pos, VideoColor color ){
    put_pixel_raw( x_y_to_raw(pos->x,pos->y), color );
    put_pixel_raw( x_y_to_raw(pos->x+1,pos->y), color );
}

void hal_video_clear( VideoColor color ){
	for( int y=0; y<VIDEO_MAX_Y; y++ ){
		for( int x=0; x<VIDEO_MAX_X; x++ ){
			put_pixel_raw(  x_y_to_raw(x,y), color );
		}
	}

    //go to origin
    curr_x = X_ORIGIN;
    curr_y = Y_ORIGIN;
}

static inline uint32_t x_y_to_raw(uint32_t x, uint32_t y){
	return y*VIDEO_MAX_X + x;
}

///////////////////////////////
/////// DRIVER INTERFACE
//////////////////////////////
static inline void put_pixel_raw( uint32_t raw_pos, uint32_t color ){
    *(fb + raw_pos) = color; //<<<-- Note that addition is pointer arithmetic!
}
