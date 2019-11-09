#include <stdint.h>
#include "lib/lib.h"


int main( void ){

  //This is a dummy syscall...
  //Just foe reference (see slides for week 13 part two)
  uint32_t received =  dummy( 7, 7, 7 );

 // printf( "I received: %d", received );

  return received;
}
