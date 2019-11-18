#ifndef SYSTEM_H
#define SYSTEM_H

#define main(...) kernel_main ()

void system_init(void);


//
// OS Configuration here
// (edit manually)
//

//Screen
#define SYSTEM_SCREEN_BACKGROUND_COLOR       0x232424
#define SYSTEM_SCREEN_TEXT_COLOR             VIDEO_COLOR_WHITE
#define SYSTEM_SCREEN_TEXT_SIZE              1
#define SYSTEM_SCREEN_WIDTH                  1280
#define SYSTEM_SCREEN_HEIGHT                 768
#define SYSTEM_SCREEN_DEPTH                  32

//Debugging

//IMPORTANT:
//           T H I S     I S    B R O K E N
// (if you say FALSE, it will fail on the PI. Works on QEMU though.)
#define SYSTEM_DEBUG_ON               true    //change to true/false. By default debug info goes to SerialA
// ================================================


//File System
#define SYSTEM_MAX_FAT_TABLE_SIZE_IN_SECTORS    700 //larger starts to take to long to load, shorter and files are not found
#define SYSTEM_MAX_DIRECTORY_ENTRIES            500



#endif
