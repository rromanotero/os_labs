#include <stdbool.h>		// C standard needed for bool
#include <stdint.h>			// C standard for uint8_t, uint16_t, uint32_t etc
#include "system.h"
#include "hal.h"
#include "kprintf.h"
#include "fat.h"


//         W A R N I N G:
//
//
//          NOTE THE FILE SYSTEM AND (MULTICORE THREADS + INTERRUPTS )
//             DON;T WORK TOGETHER AT THE MOMENT
//
//
//           BY ITSELF IT WORKS JUST FINE          
//
//

void display_root_dir(void);
void display_image(void);
void display_alice(void);
void print_n_chars();


uint8_t buffer[240000]; //107KB (Recall there's 3 pixels per byte + headers)

FATFile file;

int kernel_main (void) {

    system_init();  //This inits everything (should not be removed)

    display_root_dir();
	display_image();
	display_alice();

	while (1);

	return 0;
}

void print_n_chars( uint8_t* str, uint32_t len ){
	while( len-- > 0 )
		kprintf( "%c", *str++ );
}

void display_root_dir(void){
	//read root dir
	FATDirectory dir;
	fat_read_files_in_dir( &dir, "/" );

	//display directory
	//
	//   VFAT Long File Names (LFNs) are stored on a FAT file system
	//	 using a trick: adding additional entries into the directory
	//	 before the normal file entry. The additional entries are marked
	//   with the VOLUME LABEL, SYSTEM, HIDDEN, and READ ONLY attributes
	//	 (yielding 0x0F), which is a combination that is not expected
	//	 in the MS-DOS environment, and therefore ignored by MS-DOS programs
	//	 and third-party utilities.
	//
	// See https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system#VFAT_long_file_names
	//
	kprintf( "\n" );
	kprintf( "ROOT DIRECTORY:\n\n" );
	for( uint32_t i=0; i<dir.num_of_files; i++ ){

			if( dir.files[i].is_read_only
				&&  dir.files[i].is_hidden
				&&  dir.files[i].is_volume
				&&  dir.files[i].is_system )
					continue; //Skip VFAT entries

			if( dir.files[i].is_volume
				|| dir.files[i].is_hidden
			 	|| dir.files[i].is_system )
					continue; //Skip Volume, Hidden, and System entries

			print_n_chars( dir.files[i].name, FAT_MAX_FILENAME_LENGTH );
			kprintf( "   " );
			print_n_chars( dir.files[i].ext, FAT_MAX_EXT_LENGTH );
			kprintf( "   " );
			kprintf( "%d KB",  dir.files[i].size/1024 );

			kprintf( "\n" );
	}

    hal_video_puts( "\n\nPress any key to continue", 2, VIDEO_COLOR_RED  );
	hal_io_serial_getc( SerialA );
	hal_video_clear( SYSTEM_SCREEN_BACKGROUND_COLOR );

}

void display_alice(void){

	FATFile file;

	if( fat_file_open( &file, "ALICE", "TXT" ) == FAT_SUCCESS ){

		//Read to buffer
		fat_file_read( &file, buffer );
		buffer[file.size] = '\0';

		//Display
		kprintf( "ALICE.TXT (%d KB): \n\n", file.size/1024 );
		kprintf( "\n" );
		kprintf( "%s", buffer );

		hal_video_puts( "\n\nPress any key to continue", 2, VIDEO_COLOR_RED  );
		hal_io_serial_getc( SerialA );
		hal_video_clear( SYSTEM_SCREEN_BACKGROUND_COLOR );

	}else{
		hal_video_puts( "\nFILE NOT FOUND\n", 2, VIDEO_COLOR_RED );
	}

}


void display_image(void){

	FATFile file;

	if( fat_file_open( &file, "COFFEE2", "BMP" ) ==  FAT_SUCCESS ){

		//Read to buffer
		fat_file_read( &file, buffer );

		//Display
		kprintf( "\nCOFFEE2.BMP (%d KB): \n", file.size/1024 );
		hal_io_video_draw_image( buffer, 171, 211 );
        kprintf( "\n\n" );

		//hal_video_puts( "\n\nPress any key to continue", 2, VIDEO_COLOR_RED  );
		//hal_io_serial_getc( SerialA );
		//hal_video_clear();

	}else{
		hal_video_puts( "\nFILE NOT FOUND\n", 2, VIDEO_COLOR_RED );
	}


}
