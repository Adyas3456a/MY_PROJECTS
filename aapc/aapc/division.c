/************************************************************************************************
*Author         :Adyasha Nanda
*Date           :Mon 21 feb 2025 9:04:05 IST
*File           :division.c
*************************************************************************************************/

#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
   // res list storing the subs result
    Dlist *headres = NULL, *tailres = NULL;

    //increment list for main result list always contains 1
    Dlist *headinc = NULL, *tailinc = NULL;
    insert_at_first(&headinc, &tailinc, 1);

    //two strings for 2 lists 
    char str1[100], str2[100];
    //initially main res list contains 1 because if division was possible then only division func was called
    insert_at_first(&(*headR), &(*tailR), 1);
    //since list 2 is constant it will not change so no need to convert again and again we can convert it outside only
    list_to_string(str2, *head2);
    
    while(1)
    {
       //do substraction store result in res list
        subtraction(&(*head1), &(*tail1), &(*head2), &(*tail2), &(headres), &(tailres));
        
        //delete 1st list and update with res list
        delete_list(&(*head1), &(*tail1));
        *head1 = headres;
        *tail1 = tailres;
        //assign null to res list
        headres = tailres = NULL;

        //convert 1st list to string
        list_to_string(str1, *head1);
        //compare both lists in form of strings if returns -1 go for division
       if(compare_lists_before_div(str1, str2)==-1) 
       {
         //if division possible increment main res list
          addition(&(*headR), &(*tailR), &headinc, &tailinc, &headres, &tailres);
          delete_list(&(*headR), &(*tailR));
          *headR = headres;
          *tailR = tailres;
          headres = tailres = NULL;
       }
       else
       {
          if(!strcmp(str1, str2))
          {
            //if both  list are same (5/5) division possible increment main res list
               addition(&(*headR), &(*tailR), &headinc, &tailinc, &headres, &tailres);
               delete_list(&(*headR), &(*tailR));
               *headR = headres;
               *tailR = tailres;
               headres = tailres = NULL;
          }
          break;
       }
    }  
    //delete local lists
    delete_list(&headinc, &tailinc);
    delete_list(&headres, &tailres);
    return SUCCESS;

}
