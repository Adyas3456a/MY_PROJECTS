/************************************************************************************************
*Author         :Adyasha Nanda
*Date           :Mon 21 feb 2025 9:04:05 IST
*File           :fun.c
*************************************************************************************************/

#include "apc.h"

char sign_flag=0;
char sign_flag_n1=0, sign_flag_n2=0;

void remove_zeroes(char **str1, char **str2)
{
    //setting sign flags
    if((*str1)[0]=='-')   
        sign_flag_n1 = 1;  
    
    if((*str2)[0]=='-')
        sign_flag_n2 = 1;
    
    int i = 0;
    while ((*str1)[i]) 
    {
        if ((*str1)[i] == '+' || (*str1)[i] == '-')
        {
            i++;
            continue;
        }

        if ((*str1)[i] == '0')
            i++;
        else
            break;
    }

    if ((*str1)[i] == '\0')
        *str1 = *str1 + --i;
    else
        *str1 = *str1 + i;

    i = 0; 
    while ((*str2)[i]) 
    {
        if ((*str2)[i] == '+' || (*str2)[i] == '-')
        {
            i++;
            continue;
        }

        if ((*str2)[i] == '0')
            i++;
        else
            break;
    }

    if ((*str2)[i] == '\0')
        *str2 = *str2 + --i;
    else
        *str2 = *str2 + i;
}



int read_and_valid_arg(char *str)
{
    if(!(str[0]=='-' || str[0]=='+' || isdigit(str[0])))
        return FAILURE;
    int i=1;
    while (str[i])
    {
        if(!isdigit(str[i]))
        {
            return FAILURE;
        }
        i++;
    }
    return SUCCESS;
}

char check_operation(char **argv)
{
    if(argv[2][0]=='+')
    {
        if(sign_flag_n1 && sign_flag_n2)   //-100 + -500
        {
            return '+';
        }
        else if(sign_flag_n1 && !sign_flag_n2)
        {
            if(atoi(argv[1]) < atoi(argv[3]))  // -200 + 1000
            {
                return '-';
            }
            else if(atoi(argv[1]) > atoi(argv[3])) // -1000 + 200
            {
                sign_flag_n2 = 1;
                return '-';
            }
            else
                return '-';
        }
        else if(sign_flag_n2 && !sign_flag_n1)
        {
            if(atoi(argv[1]) < atoi(argv[3])) //200 + -1000
            {
                sign_flag_n1 = 1;
                return '-';
            }
            else if(atoi(argv[1]) > atoi(argv[3])) // 1000 + -200
            {
                return '-';
            }
            else                    
                return '-';
        }
        else                                    // 100 + 100
            return '+';
    }
    else if(argv[2][0]=='-')
    {
        if(!sign_flag_n1 && !sign_flag_n2)   //both +ve
        {
            if(atoi(argv[1]) < atoi(argv[3]))        //10 - 20
            {
                sign_flag_n1 = sign_flag_n2 = 1;
                return '-';
            }
            else if(atoi(argv[1]) > atoi(argv[3]))        //30 - 20
            {
                return '-';
            }
            else                                //equal
                return '-';
        }
        else if(sign_flag_n1 && !sign_flag_n2)  //-10 - +20
        {
            sign_flag_n2 = 1;
            return '+';
        }
        else if(!sign_flag_n1 && sign_flag_n2)  // 10 - -20
        {
            return '+';
        }
        else                                   // both -ve (-10 - -20    -20 - -10)
        {
            printf("here\n");
            if(atoi(argv[1]) < atoi(argv[3]))  // -10 - -20
            {
                sign_flag_n1 = sign_flag_n2 = 0;
                return '-';
            }
            else if(atoi(argv[1]) > atoi(argv[3]))  // -20 - -10
            {
                sign_flag_n1 = sign_flag_n2 = 1;
                return '-';
            }
            else
                return '-';
        }
    }
    else if(argv[2][0] == '/' || argv[2][0] == 'X' || argv[2][0] == 'x' || argv[2][0] == '*')
    {
        if(sign_flag_n1 && sign_flag_n2)
        {
            sign_flag_n1 = sign_flag_n2 = 0;
        }
        else if(sign_flag_n1 || sign_flag_n2)
        {
            sign_flag_n1 = sign_flag_n2 = 1;
        }
        if(argv[2][0]=='/')
            return '/';
        else    
            return '*';
    }
}

void digit_to_list(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[])
{
    char i=0;
    while (argv[1][i])
    {
        if(isdigit(argv[1][i]))
            insert_at_last(&(*head1), &(*tail1), argv[1][i]-'0');
        i++;
    }

    i=0;
    while (argv[3][i])
    {
        if(isdigit(argv[3][i]))
            insert_at_last(&(*head2), &(*tail2), argv[3][i]-'0');
        i++;
    }
}

int insert_at_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = (Dlist*)malloc(sizeof(Dlist));
    if(new == NULL)
        return FAILURE;
    new->data = data;
    new->prev = new->next = NULL;

    if(*head == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }

    (*tail)->next = new;
    new->prev = *tail;
    *tail = new;
    return SUCCESS;

}

int insert_at_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = (Dlist*)malloc(sizeof(Dlist));
    new->data = data;
    new->prev = new->next = NULL;

    if(*head==NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }

    (*head)->prev = new;
    new->next = *head;
    *head = new;

    return SUCCESS;

}

void print_list(Dlist *head)
{ 
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    while (head)		
	    {
    	    printf("%d", head -> data);
		    head = head -> next;  
	    }
    	printf("\n");
    }
}

int compare_lists_before_sub(char *argv[])
{
    char *temp;
    if(strlen(argv[1]) > strlen(argv[3]))   // 200 - 10
    {
        return SUCCESS;
    }
    if(strlen(argv[1]) < strlen(argv[3]))   // 10 - 200
    {
        temp = argv[3];
        argv[3] = argv[1];
        argv[1] = temp;
    }
    else  if(strcmp(argv[1], argv[3]) > 0)   //200 - 100
    {
        return SUCCESS;
    }
    else  if(strcmp(argv[1], argv[3]) < 0)  //220 - 230
    {
        temp = argv[3];
        argv[3] = argv[1];
        argv[1] = temp;
    }
    return SUCCESS;

}

int compare_lists_before_div(char *str1, char *str2)
{
    if(str2[0]=='0')    // 10/0 (infinite)
        return 8;

    if(str1[0]=='0')     // 0/10
        return 0;

    if(strlen(str1) < strlen(str2))   // 12/120
    {
        return 0;
    }

    if(strlen(str1) == strlen(str2))   
    {
        if(!strcmp(str1, str2))       // 12/12
            return 1;
        if(strcmp(str1, str2) < 0)    // 20/22
            return 0;        
    }

    return -1;  //go for division


}

int delete_list(Dlist **head, Dlist **tail)
{
    if(*head==NULL)
        return FAILURE;

    Dlist *temp = *head;
    while (*head != NULL)
    {
        temp = *head;
        *head = temp->next;
        free(temp);
    }
    *head = NULL;
    *tail = NULL;
    return SUCCESS;
    
}

int delete_zeroes_from_list(Dlist **head, Dlist **tail)
{

    if(*head==NULL)
        return FAILURE;

    Dlist *temp = *head;
    while ((*head)->data==0)
    {
        temp = *head;
        *head = temp->next;
        (*head)->prev = NULL;
        free(temp);
    }
    return SUCCESS;
    
}

void list_to_string(char *str, Dlist *head)
{
    if(head==NULL)
        return ;

    int i=0;
    while (head)
    {
        str[i++] = head->data + '0';
        head = head->next;
    }
    str[i] = '\0';
}
