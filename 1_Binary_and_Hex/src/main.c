/**
*   This file is part of computer_architecture_labs
*   (https://github.com/rromanotero/computer_architecture_labs).
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
#include "uart.h"

extern uint64_t _bitwise_count_leading_zeroes_binary_64_bits( uint64_t );
extern uint64_t _bitwise_2_to_the_nth_64_bits( uint32_t );
extern uint32_t _bitwise_xor_swap_64_bits( uint64_t );
extern uint64_t _bitwise_swap_endianness_64_bits( uint64_t );
extern uint64_t _bitwise_hex_digit_repeat_64_bits( uint8_t );

void main(){
    uart_init();

    uart_puts( "Leading zeroes in (64-bit)1\n" );
    uart_puthex_64_bits(
            _bitwise_count_leading_zeroes_binary_64_bits(
                  0b0000000000000000000000000000000000000000000000000000000000000001 ));

    uart_puts( "\n\nHex Digit repeat 0x0A\n" );
    uart_puthex_64_bits(
            _bitwise_hex_digit_repeat_64_bits( 0xA0 ) );

    uart_puts( "\n\nSwap endianness of 0x0102030405060708 \n" );
    uart_puthex_64_bits(
            _bitwise_swap_endianness_64_bits( 0x0102030405060708 ) );

    uart_puts( "\n\n(2^32)-1\n" );
    uart_puthex_64_bits( 
            _bitwise_2_to_the_nth_64_bits( 32 ) - 1 );

    //Echo back everything
    while(1) uart_putc( uart_getc() );
}
