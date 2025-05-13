#include "inverted_search.h"

void search_database(Hash_t *h_table)
{
    char word[WORD_SIZE], index;
    printf("Enter the word you want to search in database : ");
    scanf("%s", word);
    
    if(word[0]>='a' && word[0]<='z')
    {
        index = word[0] - 'a';
    }
    else if(word[0]>='A' && word[0]<='Z')
    {
        index = word[0] - 'A';
    }
    else if(isdigit(word[0]))
    {
        index = 26;
    }
    else
    {
        index = 27;
    }

    if(h_table[index].main_link==NULL)
    {
        printf("INFO: Data not found\n");
        return ;
    }
    Main_node *temp_main = h_table[index].main_link;
    while (temp_main)
    {
        if(!strcmp(temp_main->word, word))
        {
            printf("Word %s is present in %d files\n", temp_main->word, temp_main->filecount);
            Sub_node *temp_sub = temp_main->sub_link;
            while (temp_sub)
            {
                printf("In file %s %d times\n", temp_sub->filename, temp_sub->wordcount);
                temp_sub = temp_sub->sub_link;
            }
            return; 
        }
        temp_main = temp_main->main_link;
    }

    printf("INFO: Data not found\n");
    return ;
    
}