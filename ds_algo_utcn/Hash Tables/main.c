#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>


typedef struct node{
    char* name;
    struct node* next;
    }node;

node* first[26] = {NULL};

/*
 * takes a string and hashes it into the correct bucket
 */
int hash(const char* buffer)
{
    // assign a number to the first char of buffer from 0-25
    return tolower(buffer[0]) - 'a';
}

void insertNode(int key, const char* buffer)
{
    // try to instantiate node to insert word
    node* newptr = malloc(sizeof(node));
    if (newptr == NULL)
    {
        return;
    }

    // make a new pointer
    strcpy(newptr->name, buffer);
    newptr->next = NULL;

    // check for empty list
    if (first[key] == NULL)
    {
       first[key] = newptr;
    }
    // check for insertion at tail
    else
    {
        node* predptr = first[key];
        while (true)
        {
            // insert at tail
            if (predptr->next == NULL)
            {
                predptr->next = newptr;
                break;
            }

            // update pointer
            predptr = predptr->next;
        }
    }
}

void Insert()
{
    char* name;
    printf("Insert key: ");
    scanf("%s", name);
    // hash the name into a spot
    int hashedValue = hash(name);

    // insert the name in table with hashed value
    insertNode(hashedValue, name);
}

int main()
{

    int opt = 32000;

    while(opt==32000 || opt!=0){
        printf("\n0.Exit\n1.Insert");
        printf("\n\nYour option is = ");
        scanf("%d", &opt);
        switch (opt)
		{
		case 0:
			break;
		case 1:
			Insert();
			break;

    }

    return 0;
}
}
