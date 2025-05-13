#include "editmp3.h"

Tag_Stat edit_mp3_file(Audiomp3 *mp3)
{
    if(open_files(mp3)==Fail)
        return Fail;

    if(check_and_copy_header(mp3)==Fail)
        return Fail;
    
    if(copy_and_compare_tag(mp3)==Fail)
        return Fail;

    if(copy_remaining_data(mp3->fptr_dup_file, mp3->fptr_mp3_flie)==Fail)
        return Fail;

    if(copy_dup_to_mp3(mp3->fptr_mp3_flie, mp3->fptr_dup_file)==Fail)
        return Fail;

    return Success;
}

Tag_Stat open_files(Audiomp3 *mp3)
{
    mp3->fptr_mp3_flie = fopen( mp3->mp3_fname,"r+");

    if(mp3->fptr_mp3_flie==NULL)
    {
        printf("ERROR: Unable to open %s\n", mp3->mp3_fname);    
        return Fail;
    }

    mp3->fptr_dup_file = fopen(mp3->dup_fname,"r+");

    if(mp3->fptr_dup_file==NULL)
    {
        printf("ERROR: Unable to open %s\n", mp3->dup_fname);    
        return Fail;
    }

    return Success;
}

Tag_Stat check_and_copy_header(Audiomp3 *mp3)
{
    if(verify_header_details(mp3)==Fail)
        return Fail;
    
    rewind(mp3->fptr_mp3_flie);
    char header[10];
    fread(header, sizeof(char), 10, mp3->fptr_mp3_flie);
    fwrite(header, sizeof(char), 10, mp3->fptr_dup_file);
    
    return Success;
}

Tag_Stat copy_and_compare_tag(Audiomp3 *mp3)
{
    while (1)
    {
        char tag[5];
        int  size , tag_no, flag=0;
        fread(tag, sizeof(char), 4, mp3->fptr_mp3_flie);
        tag[4] = '\0';
        size = read_size_le(mp3->fptr_mp3_flie, sizeof(int));
        short flags;
        // fseek(mp3->fptr_mp3_flie, 2, SEEK_CUR);  //skip 2 bytes for flags
        fread(&flags, sizeof(char), 2, mp3->fptr_mp3_flie);

        if(!strcmp(tag, mp3->tags[mp3->tag_count])) 
        {
            flag = 1;
            if(modify_text(mp3->fptr_dup_file, tag, mp3->text, flags)==Fail)
                return Fail;
            fseek(mp3->fptr_mp3_flie, size, SEEK_CUR);
        }
        else 
        {
            fseek(mp3->fptr_mp3_flie, size ,SEEK_CUR);
            unsigned long skip_copy_size = ftell(mp3->fptr_mp3_flie) - ftell(mp3->fptr_dup_file);
            fseek(mp3->fptr_mp3_flie, ftell(mp3->fptr_dup_file), SEEK_SET); 
            char *copy_data = (char*)malloc((skip_copy_size+1)*sizeof(char));
            fread(copy_data, sizeof(char), skip_copy_size, mp3->fptr_mp3_flie);
            fwrite(copy_data, sizeof(char), skip_copy_size, mp3->fptr_dup_file);
            free(copy_data);
        }
        if(flag) break;
    }

    return Success;
}

Tag_Stat modify_text(FILE *fptr_dup, char *tag, char *text, short flags)
{
    int size = strlen(text);
    /*put TAG*/
    fwrite(tag, 4, 1, fptr_dup);
    /*put size in big endian*/
    put_size_big_endian(fptr_dup, size);
    /*ask for 2 bytes of flags ?*/ //can take a short variable for this
    fwrite(&flags, sizeof(char), sizeof(short), fptr_dup);
    /*put changing_text*/
    fwrite(text, sizeof(char), size, fptr_dup);
    return Success;
}


Tag_Stat put_size_big_endian(FILE *fptr, int size)
{
    int i;
    char *byte = (char*)&size;
    for(i=sizeof(int)-1; i>=0; i--)
    {
        fwrite(byte+i, sizeof(char), 1, fptr);
    }

    return Success;
}

Tag_Stat copy_remaining_data(FILE *fptr_dest, FILE *fptr_src)
{
    char ch;
    while (fread(&ch, sizeof(char), 1, fptr_src)>0)
    {
        fwrite(&ch, sizeof(char), 1, fptr_dest);
    }
    
    return Success;
}

Tag_Stat copy_dup_to_mp3(FILE *fptr_dest, FILE *fptr_src)
{
    rewind(fptr_dest);
    rewind(fptr_src);
    char ch;
    while (fread(&ch, sizeof(char), 1, fptr_src)>0)
    {
        fwrite(&ch, sizeof(char), 1, fptr_dest);
    }

    return Success;
}