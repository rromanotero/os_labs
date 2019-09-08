# Lab 3 - HAL and Fonts

### Objectives
Upon completion of this lab, the student will be able to:

1. Describe the purpose of a HAL and how it helps makes software portable
2. Explain what is the framebuffer
3. Explain in detail how fonts and printing to the screen works in computer systems
4. Using the framebuffer, write fonts and software that prints to the screen

### Tasks
Mimicking the solution demo:
1. (6 pts) Print Alice in Wonderland's excerpt (use different colours as shown in the demo)
2. (2 pts) Get the fonts to scale up and down  
3. (2 pts) Get hal_video_puts to start in from the top when reaching the end of the screen
           but not without first asking for "Enter to continue".
    HINT:
        - If using lines for fonts, check [Bitmap/ Bresenham's line algorithm](https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C).
        - Attention to detail is important (not only on this, but in any complex enough software system). It's the difference between catastrophe and sleeping soundly.
        - Break down problems into subproblems and solve them one at a time
        - Have a plan and test often


### Deliverables
1. A screenshot of the output (for task 1)
2. A very short video of the output (for task 2)
3. hal_video.c, hal.h, fonts.c, fonts.h
(Do not write code anywhere else, or I won;t be able to test it)


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

<img src="https://github.com/rromanotero/os_labs/blob/master/3_HAL_and_Fonts/images/lab_solution.jpg" width="620"/>

Solution demo here: [Lab 3 - HAL and Fonts (Demo Solution)](https://youtu.be/KXhRCAMopFM)

##### PI 3

Solution demo here: [Lab 3 - HAL and Fonts (Demo Solution 2)](https://youtu.be/zghl6RQ6Fqo)
