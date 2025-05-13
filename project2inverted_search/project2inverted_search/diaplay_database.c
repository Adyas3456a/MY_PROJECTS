/***************************************************************************************************************************************************
*Author         :Adyasha Nanda
*File           :update.c
*Title          :To update the database
****************************************************************************************************************************************************/
#include"inverted_search.h"

void display_database(Hash_t *h_table)
{
    printf("%-8s %-20s %-11s %-15s %-9s\n", "Index", "Word", "Filecount", "Filename", "Wordcount");

    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        if (!h_table[i].main_link)
            continue;

        Main_node *temp_t = h_table[i].main_link; 

        while (temp_t)
        {
            printf("%2d       %-20s %-11d ", i, temp_t->word, temp_t->filecount);

            Sub_node *temp = temp_t->sub_link; 

            for (int j = 0; j < temp_t->filecount; j++)
            {
                if (j)
                {
                    printf("%-42s", " ");
                }
                printf("%-15s %-9d\n", temp->filename, temp->wordcount);
                temp = temp->sub_link;
            }

            temp_t = temp_t->main_link;
        }
    }
    printf("DATABASE DISPLAYED\n");
}
