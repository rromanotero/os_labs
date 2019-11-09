/**
*   This file is part of os_labs
*   (https://github.com/rromanotero/os_labs).
*
*   Copyright (c) 2019 Rafael Roman Otero.
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
**/

// NOTE:
//      SO far we only want to support a FLAT ROOT DIR (no subdirs)
//      A max of 16 files/subdirectories on the root directory
//      Max filename 8 charactewrs
//      Max file name a single cluster
//      We don not suport zero-size files

#include "hal.h"
#include "fat.h"
#include "kprintf.h"

#define FAT_BYTES_PER_FAT_ENTRY                     4
#define FAT_END_OF_CHAIN_MARKER                     0x0FFFFFFF
#define FAT_SECTOR_SIZE                             512
#define FAT_CLUSTER_SIZE                            8  // I'm only using it in one place, elsewhere I use the
                                                       // sectors per cluster value read from the File System
#define FAT_MASTER_BOOT_RECORD                      0
#define FAT_DIR_ENTRY_SIZE                          0x020
#define FAT_DIR_ENTRY_FILENAME_OFFSET               0
#define FAT_DIR_ENTRY_FILENAME_LEN                  FAT_MAX_FILENAME_LENGTH
#define FAT_DIR_ENTRY_EXT_OFFSET                    (FAT_DIR_ENTRY_FILENAME_OFFSET+FAT_DIR_ENTRY_FILENAME_LEN)
#define FAT_DIR_ENTRY_EXT_LEN                       FAT_MAX_EXT_LENGTH
#define FAT_DIR_ENTRY_SIZE_OFFSET                   0x1C
#define FAT_DIR_ENTRY_SIZE_LEN_IN_BYTES             4
#define FAT_DIR_ENTRY_ATTRIBUTE_OFFSET              0x0B
#define FAT_DIR_ENTRY_VFAT_ATTRIBUTE                0x0F

//MBR Offsets
#define MBR_OFFSET_PARTITION_TYPE               0x1C2
#define MBR_OFFSET_RELATIVE_SECTOR              0x1C6
#define MBR_OFFSET_MAGIC_NUMBER                 0x01FE

//MBR Values
#define MBR_VALUE_PARTITION_TYPE_FAT32          0x0C
#define MBR_VALUE_MAGIC_NUMBER                  0xAA55

//Boot Sector Offsets
#define BOOT_SECTOR_OFFSET_BYTES_PER_SECTOR     0x0B
#define BOOT_SECTOR_OFFSET_SECTORS_PER_CLUSTER  0x0D
#define BOOT_SECTOR_OFFSET_RESERVED_SECTORS     0x0E
#define BOOT_SECTOR_OFFSET_NUM_OF_ROOT_ENTRIES  0x11
#define BOOT_SECTOR_OFFSET_MEDIA_TYPE           0x15
#define BOOT_SECTOR_OFFSET_NUM_OF_FAT_TABLES    0x10
#define BOOT_SECTOR_OFFSET_SECTORS_PER_FAT      0x24
#define BOOT_SECTOR_OFFSET_CLUSTER_COUNT        0x5C
#define BOOT_SECTOR_OFFSET_PERCENT_IN_USE       0x70
#define BOOT_SECTOR_OFFSET_MAGIC_NUMBER         0x1FE

//Boot Sector Values
#define BOOT_SECTOR_VALUE_MAGIC_NUMBER          0xAA55
#define BOOT_SECTOR_VALUE_REMOVABLE_MEDIA       0xF8

typedef struct{
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

typedef struct{
    BIOSParameterBlock bpb;
    uint32_t address;
    uint32_t fat_table_region;
    uint32_t directory_region;
    uint32_t data_region;
}BootSector;

uint32_t cluster_to_sector( uint32_t );
uint32_t offset_read_n_bytes( uint8_t*, uint32_t, uint32_t);
uint32_t get_file_first_cluster( uint8_t* fname, uint8_t* ext );
uint32_t num_of_clusters_to_sectors( uint32_t num_of_clusters );
uint32_t num_of_sectors_to_bytes( uint32_t num_of_sectors );
uint32_t cluster_to_fat_table_offset( uint32_t );

extern void *memcpy(void *dest, void *src, size_t n);
extern size_t strlen(const char * str);


uint8_t fat_table_buffer[FAT_SECTOR_SIZE*SYSTEM_MAX_FAT_TABLE_SIZE_IN_SECTORS];
uint8_t buffer[FAT_SECTOR_SIZE];
BootSector boot_sector;


uint32_t fat_init( void ){
    // --- Is the SD Card FAT Formatted? ----

    //Read in the Master Boot Record
    hal_sd_card_read_block( buffer,
                            FAT_MASTER_BOOT_RECORD,
                            1 );

    uint32_t magic_number = offset_read_n_bytes(buffer, MBR_OFFSET_MAGIC_NUMBER, 2);
    uint32_t partition_type = offset_read_n_bytes(buffer, MBR_OFFSET_PARTITION_TYPE, 1);

    if(  magic_number != MBR_VALUE_MAGIC_NUMBER  )
        return FAT_INVALID_MBR;

    if( partition_type != MBR_VALUE_PARTITION_TYPE_FAT32 )
        return FAT_NO_FAT_32_FOUND;

    //Read in the Partition's  Boot Record
    boot_sector.address = offset_read_n_bytes(buffer, MBR_OFFSET_RELATIVE_SECTOR, 4);
    hal_sd_card_read_block( buffer,
                            boot_sector.address,
                            1 );

    magic_number = offset_read_n_bytes(buffer, BOOT_SECTOR_OFFSET_MAGIC_NUMBER, 2);

    if(  magic_number != BOOT_SECTOR_VALUE_MAGIC_NUMBER )
            return FAT_INVALID_VBR;

    // --- Read in the BIOS Parameter BLock ---
    boot_sector.bpb.bytes_per_sector = offset_read_n_bytes( buffer, BOOT_SECTOR_OFFSET_BYTES_PER_SECTOR, 2 );
    boot_sector.bpb.sectors_per_cluster = offset_read_n_bytes( buffer, BOOT_SECTOR_OFFSET_SECTORS_PER_CLUSTER, 1 );
    boot_sector.bpb.reserved_sectors = offset_read_n_bytes( buffer, BOOT_SECTOR_OFFSET_RESERVED_SECTORS, 2 );
    boot_sector.bpb.num_of_fat_tables = offset_read_n_bytes( buffer, BOOT_SECTOR_OFFSET_NUM_OF_FAT_TABLES, 1 );
    boot_sector.bpb.num_of_root_entries = offset_read_n_bytes( buffer, BOOT_SECTOR_OFFSET_NUM_OF_ROOT_ENTRIES, 2 );
    boot_sector.bpb.sectors_per_fat = offset_read_n_bytes( buffer, BOOT_SECTOR_OFFSET_SECTORS_PER_FAT, 2 );
    boot_sector.bpb.media_type = offset_read_n_bytes( buffer, BOOT_SECTOR_OFFSET_MEDIA_TYPE, 1 );
    boot_sector.bpb.cluster_count = offset_read_n_bytes( buffer, BOOT_SECTOR_OFFSET_CLUSTER_COUNT, 4 );
    boot_sector.bpb.percent_in_use = offset_read_n_bytes( buffer, BOOT_SECTOR_OFFSET_PERCENT_IN_USE, 1 );

    // --- Calculate some other usful info ---
    boot_sector.fat_table_region = boot_sector.address + boot_sector.bpb.reserved_sectors ;
    boot_sector.directory_region = boot_sector.fat_table_region
                                 + (boot_sector.bpb.num_of_fat_tables * boot_sector.bpb.sectors_per_fat);
	boot_sector.data_region = boot_sector.directory_region
                            + ( (boot_sector.bpb.num_of_root_entries * 32) / boot_sector.bpb.bytes_per_sector );


    //read fat fat_table
    hal_sd_card_read_block( fat_table_buffer,
                            boot_sector.fat_table_region,
                            SYSTEM_MAX_FAT_TABLE_SIZE_IN_SECTORS );

    return FAT_SUCCESS;
}


/*
*  Reads the contents of a file to buf
*/
void fat_file_read( FATFile* file,  uint8_t* buf ){
    uint8_t* pbuf = buf;
    uint32_t cluster = file->first_cluster;

    do{
        //Read a whole block (cluster),
        hal_sd_card_read_block( pbuf,
                                cluster_to_sector(cluster),
                                num_of_clusters_to_sectors(1)  );

        pbuf += num_of_sectors_to_bytes( num_of_clusters_to_sectors(1) );

        //get next cluster in the chain (from FAT table)
        cluster = offset_read_n_bytes( fat_table_buffer,
                                       cluster_to_fat_table_offset(cluster),
                                       FAT_BYTES_PER_FAT_ENTRY );

    }while( cluster != FAT_END_OF_CHAIN_MARKER && cluster != 0x00 ); //We need the 0x00 because it is possible
                                                                     // that the whole FAT table is not in memory!
}


/*
*  Open file
*/
uint32_t fat_file_open( FATFile* file, uint8_t* fname, uint8_t* ext ){

    FATDirectory dir;
    fat_read_files_in_dir( &dir, "/" );

    bool found=false;
    for( uint32_t i=0; i<dir.num_of_files; i++ ){

            uint32_t matches_name=0;
            uint32_t matches_ext=0;
            if( dir.files[i].is_archive ){
                    for(uint32_t j=0; j<strlen(fname); j++ ){
                        if( dir.files[i].name[j] == fname[j] )
                            matches_name++;
                    }
                    for(uint32_t j=0; j<strlen(ext); j++ ){
                        if( dir.files[i].ext[j] == ext[j] )
                            matches_ext++;
                    }
                    if( matches_name == strlen(fname) &&  matches_ext == strlen(ext) ){
                        //Found it
                        found = true;

                        memcpy( file->name,
                                dir.files[i].name,
                                FAT_DIR_ENTRY_FILENAME_LEN );

                        memcpy( file->ext,
                                dir.files[i].ext,
                                FAT_DIR_ENTRY_EXT_LEN  );

                        file->size = dir.files[i].size;
                        file->first_cluster = dir.files[i].first_cluster;
                        file->size = dir.files[i].size;
                        file->is_volume = dir.files[i].is_volume;
                        file->is_hidden = dir.files[i].is_hidden;
                        file->is_system = dir.files[i].is_system;
                        file->is_read_only = dir.files[i].is_read_only;
                        file->is_archive = dir.files[i].is_archive;
                        file->is_directory = dir.files[i].is_directory;
                    }
            }

    }//end loop

    if( !found )
        return FAT_FILE_NOT_FOUND;

    return FAT_SUCCESS;
}

uint32_t fat_read_files_in_dir( FATDirectory* dir, uint8_t* path ){

    // W A R NI N G
    //       C U R R E N T L Y    W E   O N L Y   S U P P O R T
    //            T H E   R O O T   D I R E C T O R Y
    //
    // In theory, this line could get replaced to where the directory table
    // for a non-root dir is, and eveyrthing shpuld just work
    //

    uint32_t cluster = 2;       //Directory table is always in cluster 2
    uint32_t file_count = 0;

    do{
            //read in directory table
            hal_sd_card_read_block(
        						buffer,
        						cluster_to_sector(cluster),
        						1 ); //Single sector

            //parse table
            for(uint32_t base=0; /*base<(FAT_DIR_ENTRY_SIZE*16-(FAT_DIR_ENTRY_SIZE)-1)*/ ;base+=FAT_DIR_ENTRY_SIZE){

                if( buffer[base+FAT_DIR_ENTRY_FILENAME_OFFSET] == 0xE5 )
                        continue; //Skip deleted files

                if( buffer[base+FAT_DIR_ENTRY_FILENAME_OFFSET] == 0x00 )
                        break; //End of Directory Marker


                //filename
                memcpy( dir->files[file_count].name,
                        &buffer[base+FAT_DIR_ENTRY_FILENAME_OFFSET],
                        FAT_DIR_ENTRY_FILENAME_LEN );
                //ext
                memcpy( dir->files[file_count].ext,
                        &buffer[base+FAT_DIR_ENTRY_EXT_OFFSET],
                        FAT_DIR_ENTRY_EXT_LEN  );
                //size
                dir->files[file_count].size = offset_read_n_bytes( buffer,
                                                                  base+FAT_DIR_ENTRY_SIZE_OFFSET,
                                                                  4 );
                //First cluster
                //(Bytes are stored separately)
                dir->files[file_count].first_cluster = (buffer[base+0x15]<<24)
                                                        + (buffer[base+0x14]<<16)
                                                        + (buffer[base+0x1B]<<8)
                                                        + (buffer[base+0x1A]);
                //Attributes
        		dir->files[file_count].is_read_only   = buffer[base+FAT_DIR_ENTRY_ATTRIBUTE_OFFSET] & 0x01 ? true : false;
        		dir->files[file_count].is_hidden      = buffer[base+FAT_DIR_ENTRY_ATTRIBUTE_OFFSET] & 0x02 ? true : false;
        		dir->files[file_count].is_system      = buffer[base+FAT_DIR_ENTRY_ATTRIBUTE_OFFSET] & 0x04 ? true : false;
        		dir->files[file_count].is_volume      = buffer[base+FAT_DIR_ENTRY_ATTRIBUTE_OFFSET] & 0x08 ? true : false;
        		dir->files[file_count].is_archive     = buffer[base+FAT_DIR_ENTRY_ATTRIBUTE_OFFSET] & 0x20 ? true : false;
            	dir->files[file_count].is_directory   = buffer[base+FAT_DIR_ENTRY_ATTRIBUTE_OFFSET] & 0x10 ? true : false;

                file_count++;

            }//end of parsing

            //get next cluster in the chain (from FAT table)
           cluster = offset_read_n_bytes( fat_table_buffer,
                                          cluster_to_fat_table_offset(cluster),
                                          FAT_BYTES_PER_FAT_ENTRY );

    }while( cluster != FAT_END_OF_CHAIN_MARKER && cluster != 0x00 );//We need the 0x00 because it is possible
                                                                     // that the whole FAT table is not in memory!

    dir->num_of_files = file_count;
}

uint32_t cluster_to_sector( uint32_t cluster ){
    //See Page 13 of MS Official Documentation
    //
    //The data region begins at Cluster 2
    //
    return boot_sector.data_region
            +( (cluster - 2) * boot_sector.bpb.sectors_per_cluster );
}

uint32_t num_of_clusters_to_sectors( uint32_t num_of_clusters ){
    return (num_of_clusters * boot_sector.bpb.sectors_per_cluster);
}

uint32_t cluster_to_fat_table_offset( uint32_t cluster ){
    return cluster*FAT_BYTES_PER_FAT_ENTRY;
}

uint32_t num_of_sectors_to_bytes( uint32_t num_of_sectors ){
    return (num_of_sectors * boot_sector.bpb.bytes_per_sector);
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
