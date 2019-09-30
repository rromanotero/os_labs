# Lab 3 - File System

### Objectives
Upon completion of this lab, the student will be able to:

1. Describe in detail some of the internals of the FAT32 File System
2. Describe in detail how file systems work at a low-level
3. Write better systems software!


### Tasks
1. (10 pts) Write a basic implementation of a FAT32 File System
    - Specifically print the contents from the root directory and read a file (as shown in the demo below)
    - You may assume filenames are 8 characters long at most
    - No support for subdirectories, just a FLAT ROOT DIR.
    - We only support files that fit in one Block (block size is provided by the FAT32 format)
    - No support for long filenames
    - No support for more than 16 directory entries
3. Bonus (at most one):
    -   (1 pts) Add support for larger files that span more than one block (i.e. Look into the File Allocation Table!)
    -   (1 pts) Run it on an actual PI
    -   (1 pts) Add code to read a BMP image and display it on screen

Notes and Hints:
- One step at a time. Bit by bit.
- Download the **SD Card image for this lab** [here](https://embedntks.com/comp4735/sd_card.img)
- To tell QEMU to use the SD Card image as SD Card use the "-drive" argument (full command below)
- Use hal_sd_card_read_block and kprintf_hex_dump to inspect sectors
- See Lecture and Labs


### Deliverables
0. fat.c and fat.h
1. A screenshot of the output (for task 1).
3. A screenshots of the output (for bonus task, if applicable).


### Resources on the WEB
- [Partition Table](https://wiki.osdev.org/Partition_Table)
- [Design of the FAT file system](https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system)
- [Write your own Operating System B02: File Allocation Table (FAT32)](https://www.youtube.com/watch?v=tEYgVwN1nRk)



### Solution sample for this Lab
##### QEMU
Note the VOLUME NAME is COMP4735

```bash
qemu-system-aarch64 -M raspi3 -kernel .\3_File_System\output\kernel8.img -drive file=.\3_File_System\sd_card\sd_card.img,if=sd,format=raw -serial stdio -serial null
```

<img src="https://github.com/rromanotero/os_labs/blob/master/3_File_System/images/lab_solution.png" width="580"/>


##### PI 3

Alice.txt is not getting printed. My guess is, since we only support 16 directory entries, Alice.txt is not part of the first 16. Note BOOT is the VOLUME NAME, so we have the right partition!

<img src="https://github.com/rromanotero/os_labs/blob/master/3_File_System/images/lab_solution_pi.jpg" width="580"/>
