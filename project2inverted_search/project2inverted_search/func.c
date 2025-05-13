#include "inverted_search.h"

int read_and_validate_args(char **argv, Slist **head)
{
    FILE *fp;
    int i=1;
    while (argv[i])
    {
        if (strlen(argv[i]) > 4)
        {
            if(strstr(argv[i], ".txt.txt"))
            {
                printf("INFO: %s is not .txt file\n", argv[i]);
            }
            else if(!strcmp(argv[i] + strlen(argv[i]) - 4, ".txt"))
            {
                //check for empty file remaining
                fp = fopen(argv[i],"r");
                if(fp)
                {
                    if(is_file_empty(fp) == SUCCESS)
                    {
                        printf("INFO: %s is empty file\n", argv[i++]);
                        continue;
                    }

                    if(add_to_file_list(&(*head), argv[i])==DUPLICATE)
                    {
                        printf("INFO: %s is already available\n", argv[i]);
                    }
                    else
                    {
                        printf("INFO: %s is added to list\n", argv[i]);
                    }
                }
                else
                {
                    printf("INFO: %s file is not available in current directory\n", argv[i]);
                }
                
            }
            else
            {
                printf("INFO: %s is not .txt file\n", argv[i]);
            }
        }
        else
        {
            printf("INFO: %s is not .txt file\n", argv[i]);
        } 
        i++;
    }
    
}

int add_to_file_list(Slist **head, char *filename)
{
    Slist *new = (Slist*)malloc(sizeof(Slist));
    if(!new)
        return FAILURE;
    new->file_link = NULL;
    strcpy(new->filename, filename);

    if(!*head)
    {
        *head = new;
        return SUCCESS;
    }
    Slist *temp = *head, *prev = NULL;
    while (temp)
    {
        if(!strcmp(temp->filename,filename))
        {
            free(new);
            return DUPLICATE;
        }
        prev = temp;
        temp = temp->file_link;
    }

    prev->file_link = new;
    return SUCCESS;    
}

void print_list(Slist *head)
{
    if(!head)
    {
        printf("INFO: List empty\n");
        return ;
    }
    printf("Filelist -> ");
    while (head)
    {
        printf(" %s ->", head->filename);
        head = head->file_link;
    }
    printf(" NULL\n");
    
}

void create_hashtable(Hash_t *h_table)
{
    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        h_table[i].index = i;
        h_table[i].main_link = NULL;
    }
}

int check_list_empty(Slist *filelist)
{
    if(filelist==NULL)
        return SUCCESS;

    return  FAILURE;
}

void delete_file_from_list(Slist **filelist, char *filename)
{
    if(filelist==NULL)  
        return ;

    Slist *temp = *filelist, *prev = NULL;
    while (temp)
    {
        if(!strcmp(temp->filename, filename))
        {
            if(prev)
                prev->file_link = temp->file_link;
            else
                *filelist = temp->file_link;
            free(temp);
        }
        prev = temp;
        temp = temp->file_link;
    }
    
}

int is_file_empty(FILE *fp)
{
    char ch=fgetc(fp);
    while (ch!=EOF)
    {
        ch = fgetc(fp);
        if(ch != '\n' || ch != ' ')
            return FAILURE;
    }
    return SUCCESS;
}