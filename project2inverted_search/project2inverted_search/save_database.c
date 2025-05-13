#include "inverted_search.h"

void save_database(Hash_t *h_table)
{
    char file[FILENAME_SIZE];
    FILE *fp;
    printf("Enter file name to save database: ");
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
            fp = fopen(file,"w+");
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

    printf("-------------------------SAVING DATABASE-----------------------\n");
    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        if (h_table[i].main_link==NULL)
            continue;

        Main_node *temp_t = h_table[i].main_link; 

        while (temp_t)
        {
            fprintf(fp,"#%d;%s;%d;", i, temp_t->word, temp_t->filecount);
            printf("#%d;%s;%d;", i, temp_t->word, temp_t->filecount);

            Sub_node *temp = temp_t->sub_link; 

            for (int j = 0; j < temp_t->filecount; j++)
            {
                fprintf(fp, "%s;%d;", temp->filename, temp->wordcount);
                printf("%s;%d;", temp->filename, temp->wordcount);
                temp = temp->sub_link;
            }
            fprintf(fp, "#\n");
            printf("#\n");
            temp_t = temp_t->main_link;
        }
    }
    fclose(fp);
    printf("Database saved successfully\n");
}