# Lab 1 - ISA

### Objectives
Upon completion of this lab, the student will be able to:

1. Write basic assembly with conditional branching and loops
2. Write assembly subroutines that take and return values from C code
3. Disassemble machine code that uses common instructions such as B, MOV, and ADD

### Tasks
(src/arithmetic.s contains empty subroutines)
1. (4 pts) Write the assembly routine \_arithmetic_gcd
2. (2 pts) Go through the disassembly of \_arithmetic_gcd (in output/kernel8.lss) and manually translate every instruction to binary. In the translation, highlight the instruction's opcode.
3. (4 pts) Write the assembly routine \_arithmetic_print_collatz_sequence. See [Collatz sequence algorithm here](http://mathworld.wolfram.com/CollatzProblem.html).

    NOTE:
    - **Only edit arithmetic.s**
    - For full marks use [.req](https://stackoverflow.com/questions/39554589/how-to-give-a-different-name-to-a-register-in-gnu-arm-assembler) to make more readable assembly, and use descriptive label names

HINT:
To print the Collatz sequence from assembly use:
```asm
mov x0, 7                     //uart_puthex_64_bits(7)
ldr x5, =uart_puthex_64_bits
blr x5

mov x0, '\n'                  //uart_putc('\n')
ldr x5, =uart_putc
blr x5

mov x0, '\r'                  //uart_putc('\r')
ldr x5, =uart_putc
blr x5
```
Bare in mind that calling a subroutine with blr means the current ``return address" in x30 will get overwritten. So you will need to store it on subroutine entry and restore it on subroutine return like this:

```asm
.global _print_collatz
_print_collatz:
    str	x30, [sp, #-16]!     //push ret address

    // solution
    // here...

    ldr	x30, [sp], #16        //pop ret address
    blr x30                   //return
```

### Deliverables
1. A screenshot of the output from running your solution (matching the output from the solution sample below)
2. A screenshot of the translated binary of \_arithmetic_gcd
2. arithmetic.s


### Resources on the WEB
- [ARM A64 Instruction Set Architecture](https://static.docs.arm.com/ddi0596/a/DDI_0596_ARM_a64_instruction_set_architecture.pdf)
- [The A64 Instruction Set](https://static.docs.arm.com/100898/0100/the_a64_Instruction_set_100898_0100.pdf)
- [ARMv8 A64 Quick Reference](https://courses.cs.washington.edu/courses/cse469/18wi/Materials/arm64.pdf)
- [ARM Architecture Reference Manual](https://static.docs.arm.com/ddi0487/ea/DDI0487E_a_armv8_arm.pdf?_ga=2.204759571.2043138464.1566012116-96909423.1563002005)


### Solution sample for this Lab
##### QEMU
```bash
qemu-system-aarch64 -M raspi3 -kernel .\2_ISA\output\kernel8.img -serial null -serial stdio
GCD(930,180):
000000000000001E

Collatz Sequence for 21:
0000000000000015
0000000000000040
0000000000000020
0000000000000010
0000000000000008
0000000000000004
0000000000000002
0000000000000001
```
##### PI 3
  <img src="https://github.com/rromanotero/os_labs/blob/master/1_ISA/images/lab_solution.png" width="300"/>
