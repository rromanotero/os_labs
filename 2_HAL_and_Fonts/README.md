# Lab 2 - HAL and Fonts

### Objectives
Upon completion of this lab, the student will be able to:

1. Describe the purpose of a HAL and how it helps makes software portable
2. Explain what is the framebuffer
3. Explain in detail how fonts and printing to the screen works in computer systems
4. Using the framebuffer, write fonts and software that prints to the screen

### Tasks
1. (8 pts) Print 12 characters (use different colours as shown in the demo)
    - They can be different characters to the ones in the demo
2. Pick one or the other, but not both:
    - (2 pts) Get the fonts to scale up and down (as shown in the demo)
    - (1 pts) Get hal_video_puts to start over from the top when reaching the end of the screen but not without first asking for "Enter to continue" in RED colour. (as shown in demo)

Notes and Hints:
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
3. A few Screenshots showing text wrapping around to the beginning (for task 2)

### Hints
Try this, see what happens
```c
for(uint32_t i=0; i<SYSTEM_SCREEN_WIDTH*SYSTEM_SCREEN_LENGTH; i++)
    put_pixel_raw( i, 0xFFFFFFFF );
```
If you're keeping X,Y coordinates instead of raw linear pixel locations, this is how I convert an x,y coordinate to a linear (raw) location
```c
uint32_t x_y_to_raw(uint32_t x, uint32_t y){
	return y*SYSTEM_SCREEN_WIDTH + x;
}
```
This is my absolute value function (you'll need this if you're doing lines)
```c
int32_t abs(int32_t v){
		if(v<0) return v*(-1);
		else return v;
}
```

### Resources on the WEB
- [The Font Magicians - Computerphile](https://www.youtube.com/watch?v=jAdspOtgciQ)


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

<img src="https://github.com/rromanotero/os_labs/blob/master/2_HAL_and_Fonts/images/lab_solution.png" width="620"/>
<img src="https://github.com/rromanotero/os_labs/blob/master/2_HAL_and_Fonts/images/lab_solution_2.png" width="620"/>

Solution demo here: [Lab 3 - HAL and Fonts (Demo Solution)](https://youtu.be/Hc10FpHZZhk)

##### PI 3

This is how it looks in the PI, when printing an excerpt from Alice in Wonderland (THIS IS JUST A DEMO! YOU DO NOT NEED TO DO THIS).

<img src="https://github.com/rromanotero/os_labs/blob/master/2_HAL_and_Fonts/images/lab_solution_pi.jpg" width="620"/>

Solution demo here: [Lab 3 - HAL and Fonts (Demo Solution 2)](https://youtu.be/zghl6RQ6Fqo)
