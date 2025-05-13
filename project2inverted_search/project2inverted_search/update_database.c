
#include "inverted_search.h"
extern int update;
void update_database(Hash_t *h_table, Slist **filelist)
{
    char file[FILENAME_SIZE];
    FILE *fp;
    printf("Enter file name to update database: ");
    scanf("%s", file);
    if (strlen(file) > 4)
    {
        if(strstr(file, ".txt.txt"))
        {
            printf("INFO: %s is not .txt file\n", file);
            return ;
        }
        else if(!strcmp(file + strlen(file) - 4, ".txt"))
        {
            printf("INFO: Opening %s\n", file);
            fp = fopen(file,"r");
            if(fp==NULL)
            {
                printf("INFO: Unable to open %s\n", file);
                return ;
            }
            printf("INFO: %s opened\n", file);
        }
        else
        {
            printf("INFO: %s is not .txt file\n", file);
            return ;
        }
    }
    else
    {
        printf("INFO: %s is not .txt file\n", file);
        return ;
    }

    //check given file is database file or not
    if((fgetc(fp))== '#')
    {
        fseek(fp, -2, SEEK_END);    
        if((fgetc(fp))=='#')
        {
            printf("Database file %s\n", file);
            rewind(fp);
            update = 1;
        }
        else
        {
            printf("INFO: Given file is not database file\n");
            return ;
        }
    }
    else
    {
        printf("INFO: Given file is not database file\n");
        return ;
    }

    printf("-------------------------UPDATING DATABASE-------------------------\n");
    char  word[WORD_SIZE], filename[FILENAME_SIZE]; 
    int index, filecount, wordcount;
    while (!feof(fp))
    {
        fscanf(fp, "#%d;%[^;];%d;", &index, word, &filecount);
        for (int i = 0; i < filecount; i++)
        {
            fscanf(fp, "%[^;];%d;", filename, &wordcount);
            printf("%d %s %d %s %d\n", index, word, filecount, filename, wordcount);
            store_in_hashtable(index, word, filename, h_table);
        }
        fscanf(fp, "#\n");
        Slist *temp = *filelist;
        while (temp)
        {
            if(!strcmp(filename, temp->filename))
            {
                delete_file_from_list(&(*filelist), filename);
            }
            temp = temp->file_link;
        }
    }
    
    printf("-------------------------DATABASE UPDATED--------------------------\n");
    
}
