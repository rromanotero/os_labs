# Lab 3 - HAL and Fonts

### Objectives
Upon completion of this lab, the student will be able to:

1. Describe the purpose of a HAL and how it helps makes software portable
2. Explain what is the framebuffer
3. Explain in detail how fonts and printing to the screen works in computer systems
4. Using the framebuffer, write fonts and software that prints to the screen

### Tasks
1. Print an excerpt of Alice in Wonderland as shown in the solution
        - (6 pts) Print Alice in Wonderland (using the colours in the solution demo)
        - (2 pts) Get the fonts to scale up and down
        - (2 pts) Get hal_video_puts to rewind when reaching the end of the screen
                  but not without first asking for "Enter to continue".

### Deliverables
1. A screenshot of the output (for task 1)
2. A very short video of the output (for task 2)
3. hal_video.c, hal.h, fonts.c, fonts.h
(Do not write code anywhere else, or I won;t be able to test it)

HINT: IF using lines, check Brasenhams Algorithm.


### Resources on the WEB
-


### Solution sample for this Lab
##### QEMU
```bash
qemu-system-aarch64 -M raspi3 -kernel .\3_HAL_and_Fonts\output\kernel8.img -serial stdio -serial null            
Zoom Out
Zoom In
Zoom In
Zoom In
Zoom Out
```
##### PI 3
  <img src="https://github.com/rromanotero/os_labs/blob/master/7_ISA/images/lab7_solution.png" width="300"/>
