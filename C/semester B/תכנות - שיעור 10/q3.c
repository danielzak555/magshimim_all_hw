#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 21
#define FRIENDS 3
enum option{PRINT = 1, ADD, REMOVE, VIP, SEARCH, REVERSE, EXIT};

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
void addToLine(personNode** head, personNode* personToAdd);
void removeFromLine(personNode** head, char nameToRemove[]);
void addVIP(personNode** head, personNode* vipPerson);
int searchInLine(personNode* head, char nameToSearch[]);
void reverseList(personNode** head);

int main()
{
    personNode* queueHead = NULL;
    int choice = 0;
    char name[MAX_LEN] = {0};
    int age = 0;
    int flag = 1;

    while (flag)
    {
        printf("\nWelcome to MagshiParty Line Management Software!\n");
        printf("\nPlease enter your choice from the following options:\n");
        printf("1 - Print line\n");
        printf("2 - Add person to line\n");
        printf("3 - Remove person from line\n");
        printf("4 - VIP guest\n");
        printf("5 - Search in line\n");
        printf("6 - Reverse line\n");
        printf("7 - Exit\n");
        scanf("%d", &choice);
        getchar();
        
        switch(choice)
        {
            case PRINT:
                printList(queueHead);
                break;
                
            case ADD:
                printf("Welcome guest!\nEnter name: ");
                myFGets(name, MAX_LEN);
                printf("Enter age: ");
                scanf("%d", &age);
                getchar();
                personNode* newPerson = createpersonNode(name, age);
                if (newPerson != NULL)
                {
                    addToLine(&queueHead, newPerson);
                }
                break;
                
            case REMOVE:
                printf("Enter name to remove: \n");
                myFGets(name, MAX_LEN);
                removeFromLine(&queueHead, name);
                break;
                
            case VIP:
                printf("VIP GUEST!\n");
                printf("Enter name: ");
                myFGets(name, MAX_LEN);
                printf("Enter age: ");
                scanf("%d", &age);
                personNode* vipPerson = createpersonNode(name, age);
                if (vipPerson != NULL)
                {
                    addVIP(&queueHead, vipPerson);
                }
                break;
                
            case SEARCH:
                printf("Enter name to search: \n");
                myFGets(name, MAX_LEN);
                searchInLine(queueHead, name);
                break;
                
            case REVERSE:
                reverseList(&queueHead);
                printf("Line reversed!\n");
                break;
                
            case EXIT:
                printf("Goodbye\n");
                freeList(queueHead);
                flag = 0;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    getchar();
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
the first node of the list
the new personNode to add
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
    int len = 0;
    len = listLength(head);
    printf("%d people in line:\n", len);
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
Function to add a person to the queue with Israeli queue logic
input: head - pointer to head, personToAdd - person to add
output: none
*/
void addToLine(personNode** head, personNode* personToAdd)
{
    char firstName[MAX_LEN] = {0};
    char secondName[MAX_LEN] = {0};
    char thirdName[MAX_LEN] = {0};
    
    printf("Enter names of 3 friends:\n");
    printf("Friend 1:");
    myFGets(firstName, MAX_LEN);
    printf("Friend 2: ");
    myFGets(secondName, MAX_LEN);
    printf("Friend 3: ");
    myFGets(thirdName, MAX_LEN);

    if (!*head)
    {
        *head = personToAdd;
        return;
    }

    personNode* curr = *head;
    personNode* friendPosition = NULL;

    while (curr)
    {
        if (strcmp(curr->name, firstName) == 0 || strcmp(curr->name, secondName) == 0 || strcmp(curr->name, thirdName) == 0)
        {
            friendPosition = curr;
            break;
        }
        curr = curr->next;
    }

    if (friendPosition != NULL)
    {
        personToAdd->next = friendPosition->next;
        friendPosition->next = personToAdd;
    }
    else
    {
        curr = *head;
        while (curr->next)
            curr = curr->next;
        
        curr->next = personToAdd;
        personToAdd->next = NULL;
    }
}

/*
Function to remove a person from the queue by name
input: head - pointer to the head of the list, nameToRemove - name to search and remove
output: none
*/
void removeFromLine(personNode** head, char nameToRemove[])
{
    personNode* curr = *head;
    personNode* prev = NULL;
    
    if (strcmp(curr->name, nameToRemove) == 0)
    {
        *head = curr->next;
        free(curr);
        printf("%s removed from line\n", nameToRemove);
        return;
    }
    
    while (curr != NULL && strcmp(curr->name, nameToRemove) != 0)
    {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr != NULL)
    {
        prev->next = curr->next;
        free(curr);
        printf("%s removed from line\n", nameToRemove);
    }
    else
    {
        printf("%s were not found\n", nameToRemove);
    }
}

/*
function to add a VIP to the front of the queue
input: pointer to the head of the list, the VIP node to add
output: none
*/
void addVIP(personNode** head, personNode* vipPerson)
{
    vipPerson->next = *head;
    *head = vipPerson;
    printf("VIP %s was added to the front of the queue.\n", vipPerson->name);
}

/*
function to search for a person in the queue
input: pointer to the head of the list, name to search for
output: 1 if found, 0 if not found
 */
int searchInLine(personNode* head, char nameToSearch[])
{
    personNode* curr = head;
    int position = 1;
    
    while (curr != NULL)
    {
        if (strcmp(curr->name, nameToSearch) == 0)
        {
            printf("%s found in line\n", nameToSearch, position);
            return 1;
        }
        curr = curr->next;
    }
    
    printf("%s not in line\n", nameToSearch);
    return 0;
}

/*
Function to reverse the queue in one pass
input: pointer to head of the list
output: none
*/
void reverseList(personNode** head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }
    
    personNode* prev = NULL;
    personNode* curr = *head;
    personNode* next = NULL;
    
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    *head = prev;
}