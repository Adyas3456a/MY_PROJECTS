#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h> 
 

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

int phone_unique(AddressBook *addressBook, char *phone)
{
	int i=0;
	for(i=0; i<addressBook->contactCount; i++)
	{
		if(!strcmp(addressBook->contacts[i].phone, phone))
		{
			printf("INFO: Please enter a unique mobile number...\n");
			return 1;
		}
	}
	return 0;
}
int email_unique(AddressBook *addressBook, char *email)
{
	int i=0;
	for(i=0; i<addressBook->contactCount; i++)
	{
		if(!strcmp(addressBook->contacts[i].email, email))
		{
			printf("INFO: Please enter a unique email id...\n");
			return 1;
		}
	}
	return 0;
}
int name_validate(char *name)
{
	//STEP1: Fetch one by one character till null character
	int i = 0;
	while(name[i] != '\0')
	{
		if(!(isalpha(name[i]) || name[i]==' '))
		{
			return 1;
			//STEP2: Check the character is alpahebet or not
			//Yes-> Move to next character, NO -> Stop the process
		}
		i++;
	}
	return 0;
}

int phone_validate(char *phone)
{
	int i = 0;
	while(phone[i] != '\0')
	{
		if(!(isdigit(phone[i])))
		{
			printf("INFO: Mobile number validation not done, Please enter valid number...\n");
			return 1;
		}
		i++;
	}
	if(i==10) return 0; 
	printf("INFO: Mobile number validation not done, Please enter valid number...\n");
	return 1;
}

int email_validate(char *email)  
{
	int i = 0, len=strlen(email);
	// if((strcmp(&email[len-10],"@gmail.com") ))
	if(!(strstr(email,"@gmail.com") ))      
	{ 
		printf("INFO: Email ID validation not done, Please enter valid email id...\n");
		printf("Entered email should have all lowercase alpha and have extension @gmail.com\n");
		return 1;
	}

	while(email[i] != '@')
	{
		if(!(islower(email[i]) || isdigit(email[i])))
		{
			printf("INFO: Email ID validation not done, Please enter valid email id...\n");
			printf("Entered email should have all lowercase alpha and have extension @gmail.com\n");
			return 1;
		}
		i++;
	}
	return 0;
}
void createContact(AddressBook *addressBook)
{
	int n;
	printf("How many contacts you want to add: ");
	scanf("%d", &n);
	int k=0;
	for(int k=0; k<n; k++)
	{
		printf("Enter contact %d\n", k+1);
		char name[20];

	    //STEP1: Read a name from user
		printf("Enter the name: ");
		//__fpurge(STDIN);
		//getchar();
		scanf(" %[^\n]", name);


	    //STEP2: Validate the name -> Alphabets
		while(name_validate(name) == 1)
		{
			printf("INFO: Name validation not done, Please enter valid name...\n");
			printf("Enter the name: ");
			scanf(" %[^\n]", name);
			//True -> Goto STEP3, False -> print error, Goto STEP1
		}

		//STEP3: Read a mobile number from user
		//STEP4: Validate the mobile number -> Digit & 10 Digits & unique
		//True -> Goto STEP5, False -> print error, Goto STEP3
		char phone[20];
		printf("Enter Mobile number: ");
		scanf(" %[^\n]", phone);
		while(phone_validate(phone) || phone_unique(addressBook, phone)) 
		{
			printf("Enter mobile number: ");
			scanf(" %[^\n]", phone);
		}

		//STEP5: Read a email_id from user
		//STEP6: Validate the email_ID -> @gmail.com & unique
		//True -> Goto STEP7, False -> print error, Goto STEP5
		char email[50];
		printf("Enter email: ");
		scanf(" %[^\n]", email);
		while(email_validate(email) || email_unique(addressBook, email))
		{
			printf("Enter email: ");
			scanf(" %[^\n]", email);
		}

		//STEP7: store into structure[contact_count]
		// int i=0;
		// for(i=0; i < addressBook->contactCount; i++);     //10  0 to 9    10 to 11
		// addressBook->contactCount++;
		strcpy(addressBook->contacts[addressBook->contactCount].name, name);
		strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
		strcpy(addressBook->contacts[addressBook->contactCount].email, email);
		addressBook->contactCount++;
		/* Define the logic to create a Contacts */
	}
}

void searchContact(AddressBook *addressBook) 
{
	/* Define the logic for search */
	//STEP1: Print the menu Based on what searching
	//STEP2: Choose the menu
 
	//1 -> Name
	//Read the name
	//Search the extered name is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.

	//2 -> Mobile_no
	//Read the mobile_no
	//Search the extered mobile_no is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.

	//3 -> Email_id
	//Read the mail_id
	//Search the extered mail_id is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.
	int choice;
	do{
		printf("\nSearch by:\n");
        printf("1. Name\n");
        printf("2. Mobile number\n");
        printf("3. Email_id\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
		
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				{
					char name[50];
					int i=0,flag=1; 
					printf("Enter the name: ");
					scanf(" %[^\n]", name);
					while(name_validate(name) == 1)
					{
						printf("INFO: Name validation not done, Please enter valid name...\n");
						printf("Enter the name: ");
						scanf(" %[^\n]", name);
					}
					for(i=0; i<addressBook->contactCount; i++)
					{
						if(!(strcmp(name, addressBook->contacts[i].name)))
						{
							printf("::::FOUND::::\n");
							flag=0;
							printf("Name-> %s Contact-> %s Email-> %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
							break;
						}
					}


					if(flag) printf("::::NOT FOUND::::");
				}
				break;

			case 2:
				{
					char phone[20];
					int i=0;
					printf("Enter mobile number: ");
					scanf(" %[^\n]", phone);
					while(phone_validate(phone) == 1)
					{
						printf("Enter mobile number: ");
						scanf(" %[^\n]", phone);
					}
					for(i=0; i<addressBook->contactCount; i++)
					{
						if(!(strcmp(phone, addressBook->contacts[i].phone)))
						{
							printf("::::FOUND::::\n");
							printf("Name-> %s Contact-> %s Email-> %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
							break;
						}
					}
					if(i==addressBook->contactCount) printf("::::NOT FOUND::::");
				}
				break;
			case 3:
				{
					char email[50];
					int i=0;
					printf("Enter email: ");
					scanf(" %[^\n]", email);
					while(email_validate(email) == 1)
					{
						printf("Enter email: ");
						scanf(" %[^\n]", email);
					}
					for(i=0; i<addressBook->contactCount; i++)
					{
						if(!(strcmp(email, addressBook->contacts[i].email)))                 
						{
							printf("::::FOUND::::\n");
							printf("Name-> %s Contact-> %s Email-> %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
							break;
						}
					}
					if(i==addressBook->contactCount) printf("::::NOT FOUND::::");
				}
				break;
			case 4:
                printf("Exiting...\n");
                break;
				
			default:
				printf("Invalid choice. Please try again.\n");

		}

	}while (choice != 4);
}



void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int choice;
	do{
		printf("\nEdit by:\n");
        printf("1. Name\n");
        printf("2. Mobile number\n");
        printf("3. Email_id\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
		
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				{
					char name[50];
					int i=0;
					printf("Enter the existing name you want to change: ");
					scanf(" %[^\n]", name);
					while(name_validate(name) == 1)
					{
						printf("INFO: Name validation not done, Please enter valid name...\n");
						printf("Enter the existing name you want to change: ");
						scanf(" %[^\n]", name);
					}
					for(i=0; i<addressBook->contactCount; i++)
					{
						if(!(strcmp(name, addressBook->contacts[i].name)))
						{
							printf("::::FOUND::::\n");
							char new_name[50];
							printf("Enter new name: ");
							scanf(" %[^\n]", new_name);
							while(name_validate(new_name) == 1)
							{
								printf("INFO: Name validation not done, Please enter valid name...\n");
								printf("Enter the existing name you want to change: ");
								scanf(" %[^\n]", new_name);
							}
							strcpy(addressBook->contacts[i].name, new_name);
							printf("::::NAME SUCCESSFULLY CHANGED::::\n");
							break;
						}
					}
					if(i==addressBook->contactCount) printf("::::NAME NOT FOUND::::\nTry Again...");
				}
				break;

			case 2:
				{
					char phone[20];
					int i=0;
					printf("Enter existing mobile number you want to change: ");
					scanf(" %[^\n]", phone);
					while(phone_validate(phone) == 1)
					{
						printf("Enter existing mobile number you want to change: ");
						scanf(" %[^\n]", phone);
					}
					for(i=0; i<addressBook->contactCount; i++)
					{
						if(!(strcmp(phone, addressBook->contacts[i].phone)))
						{
							printf("::::FOUND::::\n");
							char new_phone[20];
							printf("Enter new phone: ");
							scanf(" %[^\n]", new_phone);
							while(phone_validate(new_phone) == 1)
							{
								printf("Enter existing mobile number you want to change: ");
								scanf(" %[^\n]", new_phone);
							}
							strcpy(addressBook->contacts[i].phone, new_phone);
							printf("::::MOBILE NUMBER SUCCESSFULLY CHANGED::::\n");
							break;
						}
					}
					if(i==addressBook->contactCount) printf("::::MOBILE NUMBER NOT FOUND::::\nTry Again...");
				}
				break;
			case 3:
				{
					char email[50];
					int i=0;
					printf("Enter existing email you want to change: ");
					scanf(" %[^\n]", email);
					while(email_validate(email) == 1)
					{
						printf("Enter existing email you want to change: ");
						scanf(" %[^\n]", email);
					}
					for(i=0; i<addressBook->contactCount; i++)
					{
						if(!(strcmp(email, addressBook->contacts[i].email)))
						{
							printf("::::FOUND::::\n");
							char new_email[50];
							printf("Enter new phone: ");
							scanf(" %[^\n]", new_email);
							while(email_validate(new_email) == 1)
							{
								printf("Enter existing email you want to change: ");
								scanf(" %[^\n]", new_email);
							}
							strcpy(addressBook->contacts[i].email, new_email);
							printf("::::EMAIL ID SUCCESSFULLY CHANGED::::\n");
							break;
						}
					}
					if(i==addressBook->contactCount) printf("::::EMAIL NOT FOUND::::\nTry Again...");
				}
				break;
			case 4:
                printf("Exiting...\n");
                break;
			default:
				printf("Invalid choice. Please try again.\n");

		}

	}while (choice != 4);

}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	int choice;
	do{
		printf("\nDelete by:\n");
        printf("1. Name\n");
        printf("2. Mobile number\n");
        printf("3. Email_id\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
		
		scanf("%d", &choice);
		
		int flag=1;
		switch(choice)
		{
			case 1:
				{
					char name[50];
					int i=0;
					printf("Enter the existing name you want to delete: ");
					scanf(" %[^\n]", name);
					while(name_validate(name) == 1)
					{
						printf("INFO: Name validation not done, Please enter valid name...\n");
						printf("Enter the existing name you want to delete: ");
						scanf(" %[^\n]", name);
					}
					for(i=0; i<addressBook->contactCount; i++)
					{
						if(!(strcmp(name, addressBook->contacts[i].name)))
						{
							printf("::::FOUND::::\n");
							for(; i<(addressBook->contactCount)-1; i++)
							{
								strcpy(addressBook->contacts[i].name, addressBook->contacts[i+1].name);
								strcpy(addressBook->contacts[i].phone, addressBook->contacts[i+1].phone);
								strcpy(addressBook->contacts[i].email, addressBook->contacts[i+1].email); 
							}
							addressBook->contactCount--;
							flag=0;
							printf("::::SUCCESSFULLY DELETED::::");
							break;
						}
					}
					if(flag) printf("::::NAME NOT FOUND::::\nTry Again...");
				}
				break;

			case 2:
				{
					char phone[20];
					int i=0;
					printf("Enter existing mobile number you want to change: ");
					scanf(" %[^\n]", phone);
					while(phone_validate(phone) == 1)
					{
						printf("Enter existing mobile number you want to change: ");
						scanf(" %[^\n]", phone);
					}
					for(i=0; i<addressBook->contactCount; i++)
					{
						if(!(strcmp(phone, addressBook->contacts[i].phone)))
						{
							printf("::::FOUND::::\n");
							for(; i<(addressBook->contactCount)-1; i++)
							{
								strcpy(addressBook->contacts[i].name, addressBook->contacts[i+1].name);
								strcpy(addressBook->contacts[i].phone, addressBook->contacts[i+1].phone);
								strcpy(addressBook->contacts[i].email, addressBook->contacts[i+1].email); 
							}
							addressBook->contactCount--;
							printf("::::SUCCESSFULLY DELETED::::");
							flag=0;
							break;
						}
					}
					if(flag) printf("::::MOBILE NUMBER NOT FOUND::::\nTry Again...");
				}
				break;
			case 3:
				{
					char email[50];
					int i=0;
					printf("Enter existing email you want to change: ");
					scanf(" %[^\n]", email);
					while(email_validate(email) == 1)
					{
						printf("Enter existing email you want to change: ");
						scanf(" %[^\n]", email);
					}
					for(i=0; i<addressBook->contactCount; i++)
					{
						if(!(strcmp(email, addressBook->contacts[i].email)))
						{
							printf("::::FOUND::::\n");
							for(; i<(addressBook->contactCount)-1; i++)
							{
								strcpy(addressBook->contacts[i].name, addressBook->contacts[i+1].name);
								strcpy(addressBook->contacts[i].phone, addressBook->contacts[i+1].phone);
								strcpy(addressBook->contacts[i].email, addressBook->contacts[i+1].email); 
							}
							addressBook->contactCount--;
							printf("::::SUCCESSFULLY DELETED::::");
							flag=0;
							break;
						}
					}
					if(flag) printf("::::EMAIL NOT FOUND::::\nTry Again...");
				}
				break;
			case 4:
                printf("Exiting...\n");
                break;
			default:
				printf("Invalid choice. Please try again.\n");

		}

	}while (choice != 4);
}

void listContacts(AddressBook *addressBook) 
{
	printf("::::List OF CONTACTS::::\n");
	// Sort contacts based on the chosen criteria
	for(int i=0; i < addressBook->contactCount; i++)
	{
		printf("Name-> %s Contact-> %s Email-> %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
	}
	printf("::::LIST COMPLETED::::\n");
}
