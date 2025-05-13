/************************************************************************************************
*Author         :Adyasha Nanda
*Date           :Mon 21 feb 2025 9:04:05 IST
*File           :addition.c
**************************************************************************************************/
#include "apc.h"

int addition(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR)
{
	// taking local variales for num1 num2 and carry
	int num1, num2, res, carry = 0; 
	Dlist *t1 = *tail1;
	Dlist *t2 = *tail2;
	
	while (t1 || t2)
	{
		// if list has reached null assign zero
		num1 = (t1==NULL ? 0 : t1->data);   
		num2 = (t2==NULL ? 0 : t2->data); 

		res = num1 + num2 + carry;

		if(res>9) //chcek for carry
		{
			carry = 1;
			insert_at_first(&(*headR), &(*tailR), res-10);
		}
		else
		{
			insert_at_first(&(*headR), &(*tailR), res);
			carry = 0;
		}

		if(t1)
			t1 = t1->prev;
		if(t2)	
			t2 = t2->prev;
	}

	if(carry)  //if carry is not zero insert carry
		insert_at_first(&(*headR), &(*tailR), carry);

	return SUCCESS;
	
}
