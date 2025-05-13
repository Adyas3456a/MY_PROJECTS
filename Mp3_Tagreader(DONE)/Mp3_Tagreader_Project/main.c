#include "viewmp3.h"
#include "editmp3.h"

int main(int argc, char *argv[])
{
    Audiomp3
    mp3 = {NULL};
    mp3.tag_count = 0;

    mp3.tags[0] = "TIT2";
    mp3.tags[1] = "TPE1"; 
    mp3.tags[2] = "TALB";
    mp3.tags[3] = "TYER";
    mp3.tags[4] = "TCON"; 
    mp3.tags[5] = "COMM";

    if (argc == 2)
    {
        if (check_Type_of_Operation(argv) == m_help)
        {
            printf("========== HELP MENU ==========\n");
            printf("View MP3 Metadata:\n");
            printf("  ./tagreader -v <filename.mp3>\n\n");
            printf("Edit MP3 Metadata:\n");
            printf("  ./tagreader -e <option> <new_text> <filename.mp3>\n");
            printf("    -t : Edit song title\n");
            printf("    -a : Edit artist name\n");
            printf("    -A : Edit album name\n");
            printf("    -y : Edit year\n");
            printf("    -m : Edit content type\n");
            printf("    -c : Edit comment\n");
            printf("===============================\n");
        }
        else
        {
            printf("[!] Invalid arguments.\nUsage:\n");
            printf("  ./tagreader -v <filename.mp3>\n");
            printf("  ./tagreader -e <option> <new_text> <filename.mp3>\n");
            printf("  ./tagreader --help\n");
            return 0;
        }
    }
    else if (argc == 3)
    {
        if (check_Type_of_Operation(argv) == m_view)
        {
            printf("\n[🔍] Viewing MP3 metadata...\n");
            if (read_and_validate_mp3_file_view(&mp3, argv) == Success)
            {
                if (display_mp3_file(&mp3) == Success)
                {
                    printf("\n[✅] Metadata displayed successfully.\n");
                }
                else 
                {
                    printf("[❌] Failed to display metadata.\n");
                    return 0;
                }
            }
            else 
            {
                return 0;
            }
        }
        else
        {
            printf("[!] Unsupported operation.\n");
            return 0;
        }
    }
    else if (argc == 5)
    {
        if (check_Type_of_Operation(argv) == m_edit)
        {
            printf("\n[✏️] Editing MP3 metadata...\n");
            if (read_and_validate_edit_arguments(&mp3, argv) == Success)
            {
                if (edit_mp3_file(&mp3) == Success)
                {
                    printf("\n[✅] Metadata updated successfully.\n");
                }
                else
                {
                    printf("[❌] Failed to update metadata.\n");
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            printf("[!] Unsupported operation.\n");
            return 0;
        }
    }
    else
    {
        printf("[!] Invalid arguments.\nUsage:\n");
        printf("  ./tagreader -v <filename.mp3>\n");
        printf("  ./tagreader -e <option> <new_text> <filename.mp3>\n");
        printf("  ./tagreader --help\n");
    }

    /* Close files */
    if (mp3.fptr_mp3_flie) fclose(mp3.fptr_mp3_flie);
    if (mp3.fptr_dup_file) fclose(mp3.fptr_dup_file);

    /* Free allocated memory */
    if (mp3.mp3_fname) free(mp3.mp3_fname);
    if (mp3.dup_fname) free(mp3.dup_fname);
    if (mp3.text) free(mp3.text);
    if (mp3.title) free(mp3.title);
    if (mp3.artist) free(mp3.artist);
    if (mp3.album) free(mp3.album);
    if (mp3.year) free(mp3.year);
    if (mp3.genre) free(mp3.genre);
    if (mp3.comment) free(mp3.comment
    );

    return 0;
}


Type_of_Operation check_Type_of_Operation(char *argv[])
{
    if(!strcmp(argv[1], "-v"))
        return m_view;
    else if (!strcmp(argv[1], "-e"))
        return m_edit;
    else if (!strcmp(argv[1], "--help"))
        return m_help;
    else 
        return m_unsupported;
    return 0;
}

Tag_Stat read_and_validate_mp3_file_view(Audiomp3 *mp3, char *argv[])
{
    /* ./a.out -v Audiomp3
           0    1    2     */
    if(strstr(argv[2], ".mp3"))
    {
        mp3->mp3_fname = (char*)malloc(strlen(argv[2])*sizeof(char));
        strcpy(mp3->mp3_fname, argv[2]);
    }   
    else
    {
        printf("ERROR: Given file is not a mp3 file\n");
        return Fail;
    } 

    return Success;
}

Tag_Stat read_and_validate_edit_arguments(Audiomp3 *mp3, char *argv[])
{
    if(!strcmp(argv[2], "-t"))
{
    printf("-> Changing Title to: %s\n", argv[3]);
    mp3->tag_count = 0;
}
else if(!strcmp(argv[2], "-a"))
{
    printf("-> Changing Artist Name to: %s\n", argv[3]);
    mp3->tag_count = 1;
}
else if(!strcmp(argv[2], "-A"))
{
    printf("-> Changing Album Name to: %s\n", argv[3]);
    mp3->tag_count = 2;
}
else if(!strcmp(argv[2], "-y"))
{
    printf("-> Changing Year to: %s\n", argv[3]);
    mp3->tag_count = 3;
}
else if(!strcmp(argv[2], "-m"))
{
    printf("-> Changing Content Type to: %s\n", argv[3]);
    mp3->tag_count = 4;
}
else if(!strcmp(argv[2], "-c"))
{
    printf("-> Changing Comment to: %s\n", argv[3]);
    mp3->tag_count = 5;
}
else
{
    printf("[!] Invalid edit option.\n");
    printf("  Usage: ./tagreader -e <option> <new_text> <filename.mp3>\n");
    return Fail;
}

}