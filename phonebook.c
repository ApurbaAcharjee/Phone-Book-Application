#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type.h"
#include "phonebook.h"
#include "utilities.h"

#define MAX_SIZE 100

/*array to hold our contacts*/
Contact phonebook[MAX_SIZE];

/*current size of the phonebook array*/
int currentSize = 0;


void addEntry()
{
    Contact c;
    printf("Enter First Name: ");
    gets(c.firstName);
    printf("Enter Last Name: ");
    gets(c.lastName);
    printf("Enter Mobile Number: ");
    gets(c.mobileNumber);

    phonebook[currentSize] = c;
    ++currentSize;

    printf("\nContact Added.\n");
}


void display(int index)
{
    if(index < 0 || index >= currentSize)
    {
        puts("Error: invalid index!");
        return;
    }
    Contact c = phonebook[index];
    printf("First Name: %s\n", c.firstName);
    printf("First Name: %s\n", c.lastName);
    printf("First Name: %s\n", c.mobileNumber);

}

void displayAll()
{
    if(currentSize == 0)
    {
        puts("Phonebook is Empty!");
        return;
    }
    int i;
    for(i=0; i<currentSize; i++)
    {
        display(i);
        puts("");// extra new line
    }
}

void search(char *key, search_t type)
{
    int found = 0;
    int i;

    strtolower(key);
    char content[41];

    if(type == FIRST_NAME)  //search by first name
    {
        for(i=0; i<currentSize; i++)
        {
            strcpy(content, phonebook[i].firstName);
            strtolower(content);
            if(strcmp(content, key) == 0)
            {
                display(i);
                found = 1;
            }
        }
    }
    else if(type == LAST_NAME)  // search by last name
    {
        for(i=0; i<currentSize; i++)
        {
            strcpy(content, phonebook[i].lastName);
            strtolower(content);
            if(strcmp(content, key) == 0)
            {
                display(i);
                found = 1;
            }
        }
    }
    else if(type == MOBILE_NUMBER)  //search by mobile number
    {
        for(i=0; i<currentSize; i++)
        {
            strcpy(content, phonebook[i].mobileNumber);
            strtolower(content);
            if(strcmp(content, key) == 0)
            {
                display(i);
                found = 1;
            }
        }
    }

    else
    {
        puts("Error: invalid search!");
        return;
    }
    if(!found)
    {
        puts("Not found in the phone book");
    }
}


void removeEntry(char *mobileNumber)
{

    if(currentSize == 0)
    {
        puts("Phonebook is empty! Nothing to delete!");
        return;
    }

    int i, j;
    int count = 0;
    for(i=0; i<currentSize; i++)
    {
        if(strcmp(phonebook[i].mobileNumber, mobileNumber) == 0)
        {
            for(j=i; j<currentSize-1; j++)
            {
                phonebook[j] = phonebook[j+1];
            }
            strcpy(phonebook[j].firstName, "");
            strcpy(phonebook[j].lastName, "");
            strcpy(phonebook[j].mobileNumber, "");

            currentSize -= 1;
            ++count;
        }
    }
    if(count == 0)
    {
        puts("No entry deleted");
    }
    else
    {
        printf("%d entries deleted\n", count);
    }
}


void readFromFile()
{
    FILE *fp;
    if((fp = fopen("phonebook.db", "rb")) == NULL)
    {
        puts("Error: can't load the database file!");
        return;
    }

    /* read the size of the phonebook */
    if(fread(&currentSize, sizeof(currentSize), 1, fp) != 1)
    {
        puts("Error: can't read data!");
        return;
    }

    /* read the actual phonebook content */
    if(fread(phonebook, sizeof(phonebook), 1, fp) != 1)
    {
        puts("Error: can't read data!");
        return;
    }

}

void saveToFile()
{
    FILE *fp;
    if((fp = fopen("phonebook.db", "wb")) == NULL )
    {
        puts("Error: can't create a database file!");
        return;
    }
    /* Save the curren size of the phone book */
    if(fwrite(&currentSize, sizeof(currentSize), 1, fp) != 1)
    {
        puts("Error: can't save data!");
        return;
    }
    /* Save the phonebook content */
    if(fwrite(phonebook, sizeof(phonebook), 1, fp) != 1)
    {
        puts("Error: can't save data!");
        return;
    }
    puts("Phonebook saved to file successfully!");
}

/*
    *Student Database
    *Inventory Management
*/
