/************************************************************************************************
*Author         :Adyasha Nanda
*Date           :Mon 21 feb 2025 9:04:05 IST
*File           :multiplication.c
*************************************************************************************************/
#include "apc.h"

int multiplication(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR)
{
	Dlist *t1 = *tail1;
	Dlist *t2 = *tail2;
	
	//two extra lst pointers for storing multiplication res and for back up
	Dlist *headM = NULL, *tailM = NULL;  //multiplication result
	Dlist *headB = NULL, *tailB = NULL;  // back up list
	//local variables
	int count = 0, carry=0, num1, num2, mul=0;;
	insert_at_first(&(*headR), &(*tailR), 0);  
	while (t2)
	{
		t1 = *tail1;
		num2 = t2->data;
		carry = 0;
		while (t1!=NULL)
		{
			num1 = t1->data;
			mul = (num1 * num2) + carry;
			carry = mul / 10;  
			mul = mul % 10;
			insert_at_first(&(headM), &(tailM), mul);

			t1 = t1->prev;
		}
		if(carry) //if carry is nnon zero inerst carry
			insert_at_first(&(headM), &(tailM), carry);

		// add multiplication list and result list store result in back up list
		addition(&headM, &tailM, &(*headR), &(*tailR), &(headB), &(tailB));
		
		//assign back up list to result list
		*headR = headB; 
		*tailR = tailB;
		delete_list(&headM, &tailM); //delete multiplpication list for next iteration
		//assign null to back up list
		headB = NULL; 
		tailB = NULL;
		count++;
		//add zeroes based on count in multiplication list before next iteration 
		for (int i = 0; i < count; i++)
		{
			insert_at_first(&headM, &tailM, 0);
		}

		t2 = t2->prev;
	}
	//delete multiplication list 
	delete_list(&headM, &tailM);
}
