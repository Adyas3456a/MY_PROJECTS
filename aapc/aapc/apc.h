/************************************************************************************************
*Author         :Adyasha Nanda
*Date           :Mon 21 feb 2025 9:04:05 IST
*File           :apc.c
*************************************************************************************************/
#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
	struct node *prev;
	int data;
	struct node *next;
}Dlist;


/* Include the prototypes here */

/*Read and validate arguments*/
int read_and_valid_arg(char *str);

/*Check operation to perform on operands*/
char check_operation(char **argv);

/*Insert at last*/
int insert_at_last(Dlist **head, Dlist **tail, int data);

/*Insert at first*/
int insert_at_first(Dlist **head, Dlist **tail, int data);

/*Remove zeroes if available*/
void remove_zeroes(char **str1, char **str2);

/*Compare lists before substraction*/
int compare_lists_before_sub(char *argv[]);

/*Compare lists before division*/
int compare_lists_before_div(char *str1, char *str2);

/*Store the operands into the list */
void digit_to_list(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[]);

/*List to digit*/
void list_to_string(char *str, Dlist *head);

/*Addition */
int addition(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*Subtraction*/
int subtraction(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*Multiplication*/
int multiplication(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*Division */
int division(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*Print the list*/
void print_list(Dlist *head);

/*Delete list*/
int delete_list(Dlist **head, Dlist **tail);

/*Delete nodes containing zero from list*/
int delete_zeroes_from_list(Dlist **head, Dlist **tail);

// char sign_flag_n1=0, sign_flag_n2=0;
#endif
