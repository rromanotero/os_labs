# Lab 3 - Single Process

### Objectives
Upon completion of this lab, the student will be able to:

1. ...

### Tasks
(src/arithmetic.s contains empty subroutines)
1. (4 pts) ....

HINT:
....
```asm
.....
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
qemu-system-aarch64 -M raspi3 -kernel .\7_ISA\output\kernel8.img -serial null -serial stdio
```
##### PI 3
  <img src="https://github.com/rromanotero/computer_architecture_labs/blob/master/7_ISA/images/lab7_solution.png" width="300"/>
