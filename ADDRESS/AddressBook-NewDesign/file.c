#include <stdio.h>
#include "file.h"
#include<stdlib.h>
void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr;
    fptr = fopen("contacts.csv", "w");
    if(fptr==NULL)
    {
        printf("File doesn't exist\n");
        exit(0);
    }
    int i;
    fprintf(fptr ,"#%d#\n", addressBook->contactCount);
    for(i=0; i<addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s, %s, %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }    
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr;
    fptr = fopen("contacts.csv", "r");
    if(fptr==NULL)
    {
        printf("File doesn't exist\n");
        exit(0);
    }
    int i;
    fscanf(fptr ,"#%d#\n", &addressBook->contactCount);
    for(i=0; i<addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,], %[^,], %[^\n]", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }    
    fclose(fptr);
}
