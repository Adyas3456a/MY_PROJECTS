#ifndef MP3_EDIT_H
#define MP3_EDIT_H

#include "util.h"
#include "viewmp3.h"   //for check header details and get size little endian

/*Read and validate edit arguments */
Tag_Stat read_and_validate_edit_arguments(Audiomp3 *mp3, char *argv[]);

/*Edit mp3 file*/
Tag_Stat edit_mp3_file(Audiomp3 *mp3);

/*Open mp3 and duplicate file*/
Tag_Stat open_files(Audiomp3 *mp3);

/*check and copy header*/
Tag_Stat check_and_copy_header(Audiomp3 *mp3);

/*Get size in little endian*/    //mp3view.h

/*Compare tag and copy other data*/
Tag_Stat copy_and_compare_tag(Audiomp3 *mp3);

/*Modify text*/
// Tag_Stat modify_text(Audiomp3 *mp3, char *tag);
Tag_Stat modify_text(FILE *fptr_dup, char *tag, char *text, short flags);

/*Put size in big endian*/
Tag_Stat put_size_big_endian(FILE *fptr, int size);

/*Copy remaining data*/
Tag_Stat copy_remaining_data(FILE *fptr_dest, FILE *fptr_src);

/*Copy dup to mp3*/
Tag_Stat copy_dup_to_mp3(FILE *fptr_dest, FILE *fptr_src);
#endif