#include <stdio.h>
#include <stdlib.h>

typedef struct IntNode
{
    int val;
    struct IntNode *next;
} IntNode;

void printList(IntNode *list);
void freeList(IntNode *list);
IntNode* createNode(int value);
IntNode* addToEnd(IntNode* head, int value);
IntNode* printLastK(IntNode* head, int k, int len);

int main()
{
    IntNode *list = NULL, *kElement = NULL;
    int len = 0, value = 0, k = 0;
    
    printf("How many nodes in list? ");
    scanf("%d", &len);
    
    for (int i = 0; i < len; i++)
    {
        printf("Enter number: ");
        scanf("%d", &value);
        list = addToEnd(list, value);
        if (list == NULL)
        {
            return 1;
        }
    }
    
    printf("Choose a number k, and the k last values will be printed: ");
    scanf("%d", &k);
    
    printf("The list from that node to the end:\n");
    kElement = printLastK(list, k, len);
    if (kElement != NULL)
    {
        printList(kElement);
    }
    
    freeList(list);
    
    getchar();
    getchar();
    return 0;
}

/*
Creates a new IntNode with the given value.
input: The integer value to store in the new node.
output: A pointer to the newly allocated IntNode. Returns NULL if memory allocation fails.
*/
IntNode* createNode(int value)
{
    IntNode* newNode = (IntNode*)malloc(sizeof(IntNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

/*
Adds a new node with the given value to the end of the list.
input: The head of the linked list.
And The integer value to add.
output: The head of the list.
*/
IntNode* addToEnd(IntNode* head, int value)
{
    IntNode* newNode = createNode(value);
    if(newNode == NULL)
    {
        return NULL;
    }
    
    if (head == NULL)
    {
        return newNode;
    }
    
    IntNode* current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    
    return head;
}

/*
Returns a pointer to the k-th node from the end of the list.
input: The head of the linked list.
The number of elements from the end of the list.
The total length of the list.
output: A pointer to the k-th node from the end, or NULL if invalid.

efficiancy: O(len-k)
*/
IntNode* printLastK(IntNode* head, int k, int len)
{
    IntNode* curr = head;

    if (head == NULL || k <= 0)
    {
        return NULL;
    }

    if (k >= len)
    {
        return head;
    }

    for (int i = 0; i < len - k && curr != NULL; i++)
    {
        curr = curr->next;
    }
    
    return curr;
}

/*
Recursively prints all the values in a linked list.
input: A pointer to a node in the linked list.
output: None.
*/
void printList(IntNode *list)
{
    if (list)
    {
        printf("%d ", list->val);
        printList(list->next);
    }
    else
    {
        printf("\n");
    }
}

/*
Recursively frees all nodes in a linked list.
input: A pointer to the head of the list to be freed.
output: None.
*/
void freeList(IntNode *list)
{
    if (list)
    {
        freeList(list->next);
        free(list);
    }
}