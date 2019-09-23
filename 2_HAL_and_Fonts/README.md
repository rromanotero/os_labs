# Lab 2 - HAL and Fonts

### Objectives
Upon completion of this lab, the student will be able to:

1. Describe the purpose of a HAL and how it helps makes software portable
2. Explain what is the framebuffer
3. Explain in detail how fonts and printing to the screen works in computer systems
4. Using the framebuffer, write fonts and software that prints to the screen

### Tasks
Mimicking the solution demo:
1. (8 pts) Print Alice in Wonderland's excerpt (use different colours as shown in the demo)
    - For full marks implement all letters and numbers (you can skip symbols).
2. (2 pts) Get the fonts to scale up and down (as shown in the demo)

Bonus
3. (1 pts) Get hal_video_puts to start over from the top when reaching the end of the screen
           but not without first asking for "Enter to continue" in RED colour. (as shown in demo)


HINT:
    - Only edit hal_video.c, fonts.c, and fonts.h
    - A font can be specified as a bitmap and you can have different sizes of bitmaps for different
      font sizes.
    - Alternatively, you can use lines for fonts, check [Bitmap/ Bresenham's line algorithm](https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C).
    - There's better methods for drawing resizable letters (feel free to use any).
    - Break down problems into subproblems and those subproblems into subproblems, solve them one at a time
    - Abstraction is useful in problem solving! For instance, create a Font type.


### Deliverables
0. hal_video.c, fonts.c, and fonts.h
1. A screenshot of the output (for task 1).
2. A few Screenshots showing text zooming in and out (for task 2).
3. A few Screenshots showing text wrapping around to the beginning (for task 3 bonus)


### Resources on the WEB
-


### Solution sample for this Lab
##### QEMU
```ba)sh
qemu-system-aarch64 -M raspi3 -kernel .\3_HAL_and_Fonts\output\kernel8.img -serial stdio -serial null            
Zoom Out
Zoom In
Zoom In
Zoom In
Zoom Out
```

<img src="https://github.com/rromanotero/os_labs/blob/master/2_HAL_and_Fonts/images/lab_solution.jpg" width="620"/>

Solution demo here: [Lab 3 - HAL and Fonts (Demo Solution)](https://youtu.be/KXhRCAMopFM)

##### PI 3

<img src="https://github.com/rromanotero/os_labs/blob/master/2_HAL_and_Fonts/images/lab_solution_pi.jpg" width="620"/>

Solution demo here: [Lab 3 - HAL and Fonts (Demo Solution 2)](https://youtu.be/zghl6RQ6Fqo)
