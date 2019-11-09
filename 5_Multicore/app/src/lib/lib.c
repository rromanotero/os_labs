#include "lib.h"

uint32_t dummy( uint32_t a, uint32_t b, uint32_t c ){
    uint32_t ret_val;

    asm volatile(
      "mov x3, %[input] \n"
      "mov x8, 11\n"  //Syscall nuimber
      "svc 0"
      : //output
      : [input] "r" (&ret_val) //input
      : "x30"  //Clobber registers
    );

    return ret_val;
}
