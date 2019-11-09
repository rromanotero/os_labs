

#include "hal.h"
#include "sd.h"

/*
*  HAL IO Serial Init
*/
uint32_t hal_sd_card_init( void ){
	if( sd_init() == SD_OK )
	    return HAL_SUCCESS;
     else
        return HAL_FAILED;
}

/*
*   Read a block from the SD Card
*
* params
*      buffer - buffer to read data to
*      lba - Logical Block Addressing (matches sector number, when sector size is 512)
*      block_num - num of blocks to read
*
*  returns num of block read
*/
uint32_t hal_sd_card_read_block( uint8_t* buffer, uint32_t lba,  uint32_t num_of_blocks ){
    return sd_readblock(lba, buffer, num_of_blocks);
}
