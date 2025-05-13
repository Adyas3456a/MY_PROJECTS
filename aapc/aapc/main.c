/************************************************************************************************
*Author         :Adyasha Nanda
*Date           :Mon 21 feb 2025 9:04:05 IST
*File           :main.c
*************************************************************************************************/

#include "apc.h"

//num1 and num2 sign flags
extern char sign_flag_n1, sign_flag_n2;

int main(int argc, char *argv[])
{
	/* Declare the pointers */
      
	Dlist *head1 = NULL, *tail1=NULL;
    Dlist *head2 = NULL, *tail2=NULL; 
    Dlist *headR = NULL,*tailR=NULL;

	if(argc!=4)
	{
		printf("ERROR: Insufficient number of arguments\n");
		return 0;
	}

	
	//read and check arguments
	if(read_and_valid_arg(argv[1])==FAILURE)
	{
		printf("ERROR: Invalid argument %s\n", argv[1]);
		return 0;
	}
	if(read_and_valid_arg(argv[3])==FAILURE)
	{
		printf("ERROR: Invalid argument %s\n", argv[3]);
		return 0;
	}

	printf("Operand1 = %s\nOperand2 = %s\n", argv[1], argv[3]);
	//remove unwanted zeroes and signs from operands
	remove_zeroes(&argv[1], &argv[3]);
	//check for operation
	char operator = check_operation(argv);

		switch (operator)
		{
			case '+':
				{
					/* call the function to perform the addition operation */
					digit_to_list(&head1,&tail1,&head2,&tail2,argv);
    	            addition(&head1,&tail1,&head2,&tail2,&headR,&tailR);
					if(sign_flag_n1 && sign_flag_n2)
						printf("Result = -");
					else
						printf("Result = ");
					print_list(headR);
				}                 
				break;

			case '-':	
				{
					/* call the function to perform the subtraction operation */
					if((strlen(argv[1]) == strlen(argv[3])) && !(strcmp(argv[1], argv[3])))
					{
						printf("Result = 0\n");
						return 0;
					}
					compare_lists_before_sub(argv);
					digit_to_list(&head1,&tail1,&head2,&tail2,argv);
            	    subtraction(&head1,&tail1,&head2,&tail2,&headR,&tailR);
					if(sign_flag_n1 && sign_flag_n2)
						printf("Result = -");
					else
						printf("Result = ");
					print_list(headR);
				}
				break;

			case '*':
			/* call the function to perform the multiplication operation */	
				if(argv[1][0]=='0' || argv[3][0]=='0')
				{
					printf("Result = 0\n");
					return 0;
				}
				digit_to_list(&head1,&tail1,&head2,&tail2,argv);
                multiplication(&head1,&tail1,&head2,&tail2,&headR,&tailR);
				if(sign_flag_n1 && sign_flag_n2)
					printf("Result = -");
				else
					printf("Result = ");
				print_list(headR);
				break;

			case '/':	
			/* call the function to perform the division operation */
				if(!(strcmp(argv[1], argv[3])) && (sign_flag_n1 || sign_flag_n2))
				{
					printf("Result = -1\n");
					return 0;
				}
				int res;
				res = compare_lists_before_div(argv[1], argv[3]);
				if(res==-1)
				{
					digit_to_list(&head1,&tail1,&head2,&tail2,argv);
        	        division(&head1,&tail1,&head2,&tail2,&headR,&tailR);
					if(sign_flag_n1 && sign_flag_n2)
						printf("Result = -");
					else
						printf("Result = ");
					print_list(headR);
				}
				else if(res==8)
				{
					printf("Result = Infinite\n");
				}
				else
				{
					printf("Result = %d\n", res);
				}
				break;

			default:
				printf("Invalid Input:-( Try again...\n");
		}
	return 0;
}
