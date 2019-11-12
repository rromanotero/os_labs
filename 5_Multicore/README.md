# Multicore Demo
#

This demo shows example code for:
- Drawing a square on the screen
- Moving the square with user input
- Printing to the screen
- Running Code in 4 CPU Threads
- Measuring elapsed time by reading a timer's counter
- Using a timer interrupt that *ticks* for periodic tasks

The code is in main.c. Main begins executing and creates three CPU threads, each of which will do different tasks. One will print to the screen. A second one will work together with a timer interrupt to print the number of ticks. A third one will read user input and draw a square on the screen, and a last one... I've forgotten, you can check it out.If you've written multithreaded code before you'll understand immediately what is happening.

Demoes here:
-   [Multicore Demo QEMU](https://www.youtube.com/watch?v=TbS2cbfCswM&feature=youtu.be)
-   [Multicore Demo PI](https://www.youtube.com/watch?v=hmBH0ercFr8&feature=youtu.be)

### Important

There is NO SCHEDULER in this demo, so **THREADS ARE NEVER PRE-EMPTED**. **Each of them owns a CPU and run code in it until the end of times**. Within the code I called them **CPU threads** (to make a distinction from threads). If you're understanding right you might've guessed that there can only be **4 CPU threads (once for each core)**. You can still work on a scheduler ... a multicore scheduler!


### No locks

If you have a look at the PI demo, above, you'll see output text is printed out of order (it also happens on QEMU, but less). So you'll have to be careful with race conditions! Remember read and write are atomic, so you do not need to synchronize that. **If you do need a lock, you'll have to write one yourself**. It's not difficult with hardware support.... maybe ask me how. 



### Notes
- In windows_build.ps1 edit **$GCC_BIN_PATH** (path to your gcc's bin folder) and **$QEMU_BIN_PATH**
  (path to qemu in your computer) from **windows_build.ps1** to build and run everything
- When built using specifically windows_build.ps1 it'll work both QEMU and the PI. However, for
  some odd reason when built using the **Makefile**, it'll compile and run on QEMU
  but **not on the PI** . Why? No idea. I guess Compilers can be mysterious.
- I added a **nonblocking getc**, so you can poll and continue to do something else if no key's being pressed.
- The **delays and ticks are precise on the PI**, but **not as much in QEMU** (since it's emulated, it goes slower on QEMU)
- The **demo is part of the kernel**. I was not able to get software interrupts
  (that's how system calls are made) to play well with the timer interrupts for this demo. it worked well on QEMU but the PI kept faulting and faulting. So no processes if you're using this demo!
