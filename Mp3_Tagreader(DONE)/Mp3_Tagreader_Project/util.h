#ifndef UTIL_H
#define UTIL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAXIMUM_TAGS 6

typedef struct Audiomp3
{
    char *mp3_fname;           // MP3 file name
    FILE *fptr_mp3_flie;       // MP3 file pointer
    char *dup_fname;           // Duplicate file name
    FILE *fptr_dup_file;       // Duplicate file pointer
    int mp3_fsize;
    char *tags[10];
    int tag_count;             // Used for counting tags in view/edit mode

    char *text;                // Text to change in edit mode

    // Improved tag variable names
    char *title;               // TIT2 - Title/song name
    char *artist;              // TPE1 - Lead performer/artist
    char *album;               // TALB - Album/movie/show title
    char *year;                // TYER - Year of release
    char *genre;               // TCON - Content type/genre
    char *comment;             // COMM - Comments

} Audiomp3;


typedef enum 
{
    m_view,
    m_edit,
    m_help,
    m_unsupported
}Type_of_Operation;

typedef enum 
{
    Success,
    Fail
} Tag_Stat;

typedef enum
{
    t_title,
    t_artist,
    t_album,
    t_year,
    t_genre,
    t_comment
} Edit_Type_of_Operation;


#endif