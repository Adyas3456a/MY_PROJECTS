/************************************************************************************************
*Author         :Adyasha Nanda
*Date           :Mon 21 feb 2025 9:04:05 IST
*File           :subtraction.c
*************************************************************************************************/

#include "apc.h"

int subtraction(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR)
{
	/* Definition goes here */
	//taking local var num1 num2 res and borrow
	int num1, num2, res, borrow = 0;
	Dlist *t1 = *tail1;
	Dlist *t2 = *tail2;
	 
	while (t1 || t2)
	{
		// if list has reached null assign zero
		num1 = (t1==NULL ? 0 : t1->data);
		num2 = (t2==NULL ? 0 : t2->data); 

		num1 = num1 - borrow;  
		if(num1<num2) //check borrow is req or not
		{
			borrow = 1;
			num1 += 10;
		}
		else
		{
			borrow = 0;
		}
		res = num1 - num2;
		insert_at_first(&(*headR), &(*tailR), res);
	
		if(t1)
			t1 = t1->prev;
		if(t2)	
			t2 = t2->prev;
		
	}

	//delete starting zeroes from list if available (00201 -> 201)
	delete_zeroes_from_list(&(*headR), &(*tailR));  
	return SUCCESS;

}
