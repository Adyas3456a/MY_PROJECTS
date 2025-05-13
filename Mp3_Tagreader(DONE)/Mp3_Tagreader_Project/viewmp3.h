#ifndef MP3_VIEW_H
#define MP3_VIEW_H

#include "util.h"

/*Check Operation type*/
Type_of_Operation check_Type_of_Operation(char *argv[]);
 
/*Read and validate mp3 file*/
Tag_Stat read_and_validate_mp3_file_view(Audiomp3 *mp3, char *argv[]);

/*Show mp3 file*/
Tag_Stat display_mp3_file(Audiomp3 *mp3);

/*Open mp3 file*/
Tag_Stat open_mp3_file(Audiomp3 *mp3);

/*Check header details*/
Tag_Stat verify_header_details(Audiomp3 *mp3);

/*Get content from mp3 file*/
Tag_Stat gather_mp3_content(Audiomp3 *mp3);

/*Check  tag*/
int verify_tag(char *str_tag, char **tags);

/*Get size in little endian format*/
int read_size_le(FILE *fptr, int data_type_size);

/*Read content*/
Tag_Stat extract_content(char *data_buffer, FILE *fptr, int size);

/*Print mp3 content*/
Tag_Stat Mp3_tag_output(Audiomp3 *mp3);

#endif