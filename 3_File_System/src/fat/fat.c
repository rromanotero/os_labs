// NOTE:
//      SO far we only want to support a FLAT ROOT DIR (no subdirs)
//      A max of 16 files/subdirectories on the root directory
//      Max filename 8 characters
//      Max file size is a single block
//      We don not suport zero-size files

#include "../hal/hal.h"
#include "fat.h"
#include "../kprintf/kprintf.h"

#define SECTOR_SIZE                             512
#define MASTER_BOOT_RECORD                      0

//MBR Offsets
#define MBR_OFFSET_PARTITION_TYPE               0x1C2
#define MBR_OFFSET_RELATIVE_SECTOR              0x000  //<<<<--- Careful it shuldn't  zero
#define MBR_OFFSET_MAGIC_NUMBER                 0x01FE

//MBR Values
#define MBR_VALUE_PARTITION_TYPE_FAT32          0x0C
#define MBR_VALUE_MAGIC_NUMBER                  0xAA55

//Boot sector Offsets
//...

//Boot sector values
//...

typedef struct{                     //For reference, you may use it as is (i.e. write your solution here)
                                    //or ignore it
    uint32_t bytes_per_sector;
    uint32_t sectors_per_cluster;
    uint32_t reserved_sectors;
    uint32_t num_of_root_entries;
    uint32_t media_type;
    uint32_t num_of_fat_tables;
    uint32_t sectors_per_fat;
    uint32_t cluster_count;
    uint32_t percent_in_use;
}BIOSParameterBlock; //BIOS Parameter BLock

typedef struct{ //For reference, you may use it as is (i.e. write your solution here)
                //or ignore it
    BIOSParameterBlock bpb;
    uint32_t address;
    uint32_t fat_table_region;
    uint32_t directory_region;
    uint32_t data_region;
}BootSector;


uint32_t offset_read_n_bytes( uint8_t*, uint32_t, uint32_t);
uint32_t get_file_first_cluster( uint8_t* fname );
extern void *memcpy(void *dest, void *src, size_t n);
extern size_t strlen(const char * str);


uint8_t buffer[SECTOR_SIZE];
BootSector boot_sector;


uint32_t fat_init( void ){
    // --- Is the SD Card FAT Formatted? ----

    //Read in the Master Boot Record
    hal_sd_card_read_block( buffer,
                            MASTER_BOOT_RECORD,
                            1 );

    // == DEBUG ==
    //UNCOMMENT THIS to see  a hex dump of the MBR!
    //Notice you can HIGHLIGHT a specific RANGE if BYTES by changing
    //the last two arguments
    //(It gets "highlighted" by getting a ! character prepended)
    //
    kprintf( "\n\r" );
    kprintf_hex_dump( buffer, 512, MBR_OFFSET_PARTITION_TYPE, MBR_OFFSET_PARTITION_TYPE );

    uint32_t magic_number = offset_read_n_bytes(buffer, MBR_OFFSET_MAGIC_NUMBER, 2);
    uint32_t partition_type = offset_read_n_bytes(buffer, MBR_OFFSET_PARTITION_TYPE, 1);

    // == DEBUG ==
    //UNCOMMENT THIS to see  the magic numbers and partition types
    //
    // Partition type 0x0C denotes FAT32
    kprintf( "\n\rmagic_number: %04x", magic_number );
    kprintf( "\n\rpartition_type: %02x\n\r", partition_type );

    if(  magic_number != MBR_VALUE_MAGIC_NUMBER  )
        return FAT_INVALID_MBR;

    if( partition_type != MBR_VALUE_PARTITION_TYPE_FAT32 )
        return FAT_NO_FAT_32_FOUND;

    //For reference, you may use it as is (i.e. write your solution here)
    //or ignore it and write your own functions
    //...
    //...


    return FAT_SUCCESS;
}


/*
*  WIll read at least 1 sector length of bytes
*/
void fat_read_file( uint8_t* fname, uint8_t* fbuf, uint32_t bytes_to_read  ){

    //For reference, you may use it as is (i.e. write your solution here)
    //or ignore it and write your own functions
    //...
    //...
}

uint32_t get_file_first_cluster( uint8_t* fname ){
    //For reference, you may use it as is (i.e. write your solution here)
    //or ignore it and write your own functions
    //...
    //...
}

uint32_t fat_read_files_in_root_dir( FATDirectory* dir ){

	//For reference, you may use it as is (i.e. write your solution here)
    //or ignore it and write your own functions
    //...
    //...
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

/*
*  For reading values from an offset in the MBR or VOlume Boot record
*/
uint32_t offset_read_n_bytes( uint8_t* buffer, uint32_t offset, uint32_t n_bytes ){
    uint32_t temp=0;

    for(uint32_t i=0; i<n_bytes; i++)
            temp |= (buffer[offset+i]<<(i*8));

    return temp;
}
