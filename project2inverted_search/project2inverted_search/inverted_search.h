#ifndef INVERTED_SEARCH
#define INVERTED_SEARCH

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define     FILENAME_SIZE       50
#define     WORD_SIZE           25
#define     HASHTABLESIZE       28
#define     SUCCESS             1
#define     FAILURE             0
#define     DUPLICATE           -1

typedef struct node
{
    char filename[FILENAME_SIZE];
    struct node *file_link;
}Slist;

typedef struct sub_node
{
    int wordcount;
    char filename[FILENAME_SIZE];
    struct sub_node *sub_link;
}Sub_node;

typedef struct main_node
{
    int filecount;
    char word[WORD_SIZE];
    Sub_node *sub_link;
    struct main_node *main_link;
}Main_node;

typedef struct hashtable
{
    int index;
    Main_node *main_link;
}Hash_t;

int read_and_validate_args(char **argv, Slist **head);

int add_to_file_list(Slist **head, char *filename);

int check_list_empty(Slist *filelist);

void create_hashtable(Hash_t *h_table);

void store_in_hashtable(int index, char *word, char *filename, Hash_t *h_table);

void create_database(Slist *filelist, Hash_t *h_table);

void display_database(Hash_t *h_table);

void search_database(Hash_t *h_table);

void save_database(Hash_t *h_table);

void update_database(Hash_t *h_table, Slist **filelist);

void print_list(Slist *head);

void delete_file_from_list(Slist **filelist, char *filename);

int is_file_empty(FILE *fp);

#endif