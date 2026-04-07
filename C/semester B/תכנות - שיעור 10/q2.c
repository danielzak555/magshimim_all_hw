#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 21

typedef struct personNode
{
    char name[MAX_LEN];
    int age;
    struct personNode* next;
}personNode;

personNode* createpersonNode(char name[], int age);
void insertAtEnd(personNode** head, personNode* newNode);
void printList(personNode* head);
void myFGets(char *buffer, int size);
void freeList(personNode* head);
int listLength(personNode* curr);
personNode* copyList(personNode* head);

int main()
{
    int amount = 0, i = 0, len = 0;
    personNode* first = NULL;
    personNode* firstNew = NULL;
    personNode* newNode = NULL;
    personNode* temp = NULL;
    char name[MAX_LEN] = {0};
    int age = 0;
    printf("How many people in the list? ");
    scanf("%d", &amount);
    for(i = 0; i < amount; i++)
    {
        getchar();
        printf("Enter name: ");
        myFGets(name, MAX_LEN);
        printf("Enter age: ");
        scanf("%d", &age);
        newNode = createpersonNode(name, age);
        if(newNode == NULL)
        {
            return 1;
        }
        insertAtEnd(&first, newNode);
    }
    printList(first);
    len = listLength(first);
    printf("List length: %d\n", len);
    firstNew = copyList(first);
    printList(firstNew);
    getchar();
    getchar();
    freeList(first);
    freeList(firstNew);
    
    return 0;
}

/**
Function will create a personNode with the provided age and name
input: age and name
output: personNode with the provided age and name
*/
personNode* createpersonNode(char name[], int age)
{
    personNode* newpersonNode = (personNode*)malloc(sizeof(personNode));
    if(newpersonNode == NULL)
    {
        printf("memory allocation failed\n");
        return NULL;
    }
    strcpy(newpersonNode->name, name);
    newpersonNode->age = age;
    newpersonNode->next = NULL;
    return newpersonNode;
}

/**
Function will add a person to the list
input:
head - the first node of the list
newNode - the new personNode to add
output:
none
*/
void insertAtEnd(personNode** head, personNode* newNode)
{
    if (!*head)
    {
        *head = newNode;
    }
    else
    {
        personNode* p = *head;
        while (p->next) 
        {
            p = p->next;
        }
        p->next = newNode;
    }
}
/*
regular fgets function
input: string and size
output: none
*/
void myFGets(char *buffer, int size)
{
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
/*
the fun free the whole list of persons
input: head  of the list
output: none
*/
void freeList(personNode* head)
{
    personNode* current = head;
    personNode* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}
/*
prints the whole list
input: the pointeer to head of list
output: none
*/
void printList(personNode* head)
{
    personNode* curr = head;
    while(curr != NULL)
    {
        printf("Name: %s, Age: %d\n", curr->name, curr->age);
        curr = curr->next;
    }
    
}
/*
recursive function that finds the len of list
input: pointer to element
output: len of list
*/
int listLength(personNode* curr)
{
    if (curr == NULL)
    {
        return 0;
    }
    return 1 + listLength(curr->next);
}

/*
creates a copy of the list
input: pointer head of original list
output: pointer fir new copy
*/
personNode* copyList(personNode* head)
{   
    personNode* curr = head;
    personNode* newNode = NULL;
    personNode* newFirst = NULL;

    while(curr != NULL)
    {
        newNode = createpersonNode(curr->name, curr->age);
        if(newNode == NULL)
        {
            return NULL;
        }
        insertAtEnd(&newFirst, newNode);
        curr = curr->next;
    }

    return newFirst;
}
