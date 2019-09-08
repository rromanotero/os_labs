
#ifndef HAL_H
#define HAL_H

#include <stdbool.h>
#include <stdint.h>
#include "system.h"

#define HAL_SUCCESS  0
#define HAL_FAILED  1


typedef uint32_t SerialId;
typedef uint32_t VideoColor;

enum SerialId { SerialA = 0, SerialB, SerialC, SerialD  };


///
///  D E L A Y
///
void hal_cpu_delay(uint32_t);

///
///  S E R I A L
///

uint32_t hal_io_serial_init( void );
void hal_io_serial_putc( SerialId, uint8_t );
uint8_t hal_io_serial_getc( SerialId );
void hal_io_serial_puts( SerialId, uint8_t* );

///
///  V I D E O
///

#define VIDEO_COLOR_BLACK   0x00000000
#define VIDEO_COLOR_WHITE   0x00000000
#define VIDEO_COLOR_GREEN 	0x00000000
#define VIDEO_COLOR_BLUE    0x00000000
#define VIDEO_COLOR_RED     0x00000000

uint32_t hal_video_init( void );
void hal_video_clear( void );
void hal_video_putc_x_y( uint32_t x, uint32_t y, uint8_t c, uint32_t size, VideoColor color );
void hal_video_putc( uint8_t c, uint32_t size, VideoColor color  );
void hal_video_puts( uint8_t*, uint32_t, VideoColor );

#endif
