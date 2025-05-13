#include "viewmp3.h"

Tag_Stat display_mp3_file(Audiomp3 *mp3)
{
    if (open_mp3_file(mp3) == Fail)
    {
        printf("[ERROR] Could not open file: %s\n", mp3->mp3_fname);
        return Fail;
    }

    if (verify_header_details(mp3) == Fail)
    {
        printf("[ERROR] Invalid or unsupported MP3 header.\n");
        return Fail;
    }

    if (gather_mp3_content(mp3) == Fail)
    {
        printf("[ERROR] Failed to extract MP3 metadata.\n");
        return Fail;
    }

    if (Mp3_tag_output(mp3) == Fail)
    {
        printf("[ERROR] Failed to display MP3 metadata.\n");
        return Fail;
    }

    return Success;
}

Tag_Stat open_mp3_file(Audiomp3 *mp3)
{
    mp3->fptr_mp3_flie = fopen(mp3->mp3_fname, "r");

    if (mp3->fptr_mp3_flie == NULL)
    {
        printf("[ERROR] Unable to open file: %s\n", mp3->mp3_fname);
        return Fail;
    }

    return Success;
}

Tag_Stat verify_header_details(Audiomp3 *mp3)
{
    char id[4];
    fread(id, sizeof(char), 3, mp3->fptr_mp3_flie);
    id[3] = '\0';

    if (strcmp(id, "ID3"))
    {
        return Fail;
    }

    short version = read_size_le(mp3->fptr_mp3_flie, sizeof(short));  
    if (version != 768)
    {
        return Fail;
    }

    fseek(mp3->fptr_mp3_flie, 1, SEEK_CUR);  // Skip flags
    int fsize;
    fread(&fsize, sizeof(int), 1, mp3->fptr_mp3_flie);
    mp3->mp3_fsize = fsize;
    return Success;
}

Tag_Stat gather_mp3_content(Audiomp3 *mp3)
{
    while (mp3->tag_count != MAXIMUM_TAGS)
    {
        char tag[5];
        int size, tag_no;
        fread(tag, sizeof(char), 4, mp3->fptr_mp3_flie);
        tag[4] = '\0';

        size = read_size_le(mp3->fptr_mp3_flie, sizeof(int));
        fseek(mp3->fptr_mp3_flie, 2, SEEK_CUR); // Skip flags

        tag_no = verify_tag(tag, mp3->tags);
        if (tag_no != -1)
            mp3->tag_count++;
        else
        {
            fseek(mp3->fptr_mp3_flie, size, SEEK_CUR);
            continue;
        }

        char **target = NULL;
        switch (tag_no)
        {
            case 0: target = &mp3->title; break;
            case 1: target = &mp3->artist; break;
            case 2: target = &mp3->album; break;
            case 3: target = &mp3->year; break;
            case 4: target = &mp3->genre; break;
            case 5: target = &mp3->comment; break;
            default: break;
        }

        if (target)
        {
            *target = (char *)malloc(size * sizeof(char));
            if (extract_content(*target, mp3->fptr_mp3_flie, size) == Fail)
                return Fail;
        }
    }
    return Success;
}

int verify_tag(char *str_tag, char **tags)
{
    for (int i = 0; i < 6; i++)
    {
        if (!strcmp(str_tag, tags[i]))
        {
            return i;
        }
    }
    return -1;
}

int read_size_le(FILE *fptr, int data_type_size)
{
    int size = 0;
    char *ptr = (char *)&size;
    for (int i = data_type_size - 1; i >= 0; i--)
    {
        fread(ptr + i, sizeof(char), 1, fptr);
    }
    return size;
}

Tag_Stat extract_content(char *data_buffer, FILE *fptr, int size)
{
    int idx = 0;
    for (int i = 0; i < size; i++)
    {
        char ch;
        fread(&ch, 1, 1, fptr);
        if (ch != '\0')
        {
            data_buffer[idx++] = ch;
        }
    }
    data_buffer[idx] = '\0';
    return Success;
}

Tag_Stat Mp3_tag_output(Audiomp3 *mp3)
{
    const char *divider = "═════════════════════════════════════════════════════════════════════════════";
    printf("\n%s\n", divider);
    printf("%35s\n", "🎵 MP3 TAG INFORMATION 🎵");
    printf("%s\n", divider);

    printf("🎼 %-12s : %s\n", "Title",   mp3->title);
    printf("🎤 %-12s : %s\n", "Artist",  mp3->artist);
    printf("💿 %-12s : %s\n", "Album",   mp3->album);
    printf("📅 %-12s : %s\n", "Year",    mp3->year);
    printf("🎧 %-12s : %s\n", "Genre",   mp3->genre);
    printf("📝 %-12s : %s\n", "Comment", mp3->comment);

    printf("%s\n\n", divider);
    return Success;
}
