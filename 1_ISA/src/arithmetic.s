.section ".text"
.align 2

.global _arithmetic_gcd
_arithmetic_gcd:

    // solution
    // here...

    mov x0, 0
    blr x30

.global _arithmetic_print_collatz_sequence
_arithmetic_print_collatz_sequence:
    str	x30, [sp, #-16]!     //push ret address

    // solution
    // here...

    ldr	x30, [sp], #16        //pop ret address
    blr x30                   //return
