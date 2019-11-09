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

#ifndef FAT_H
#define FAT_H

#define FAT_SUCCESS                 0
#define FAT_FILE_NOT_FOUND          1
#define FAT_INVALID_MBR             2
#define FAT_NO_FAT_32_FOUND         3
#define FAT_INVALID_VBR             4

#define FAT_MAX_FILENAME_LENGTH     8       //Given by FAT format
#define FAT_MAX_EXT_LENGTH          3       //Given by FAT format
#define FAT_MAX_DIR_ENTRIES         SYSTEM_MAX_DIRECTORY_ENTRIES

typedef struct{
    uint8_t name[FAT_MAX_FILENAME_LENGTH+1];
    uint8_t ext[FAT_MAX_EXT_LENGTH];
    uint32_t size;
    uint32_t first_cluster;
    bool is_volume;
    bool is_hidden;
    bool is_system;
    bool is_read_only;
    bool is_archive;
    bool is_directory;
}FATFile;

typedef struct FATDirectory{
    FATFile files[FAT_MAX_DIR_ENTRIES];
    uint32_t num_of_files;
}FATDirectory;



uint32_t fat_init( void );
uint32_t fat_read_files_in_dir( FATDirectory* dir, uint8_t* path );
void fat_file_read( FATFile* file,  uint8_t* buffer );
uint32_t fat_file_open( FATFile* file,  uint8_t* fname, uint8_t* ext );

#endif
