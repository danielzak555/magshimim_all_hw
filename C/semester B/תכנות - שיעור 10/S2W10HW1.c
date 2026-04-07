#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IntNode
{
  int value;
  struct IntNode* next;
} IntNode;

IntNode* createIntNode(int value);
void insertAtEnd(IntNode** head, IntNode* newNode);
void printList(IntNode* head);
int secret(IntNode* head);

int main()
{
  IntNode* first = NULL;
  IntNode* newNode = createIntNode(13);
  insertAtEnd(&first, newNode);
  newNode = createIntNode(422);
  insertAtEnd(&first, newNode);
  newNode = createIntNode(51);
  insertAtEnd(&first, newNode);
  newNode = createIntNode(6);
  insertAtEnd(&first, newNode);
  newNode = createIntNode(733);
  insertAtEnd(&first, newNode);
  
  int mySecret = secret(first);
  printf("My secret is: %d\n", mySecret);
  return 0;
}

/**
Function will create a IntNode with the provided value
input:
value
output:
IntNode with the provided value
*/
IntNode* createIntNode(int value)
{
  IntNode* newIntNode = (IntNode*)malloc(sizeof(IntNode));
  newIntNode->value = value;
  newIntNode->next = NULL;
  return newIntNode;
}

/**
Function will add a number to the numbers list
input:
head - the first node of the list
newNode - the new intNode to add
output:
none
*/
void insertAtEnd(IntNode** head, IntNode* newNode)
{
  if (!*head)
  {
    *head = newNode;
  }
  else
  {
    IntNode* p = *head;
    while (p->next) 
    {
      p = p->next;
    }
    p->next = newNode;
  }
}

/**
A secret function
input: the list (the first intNode)
output:
none
*/
int secret(IntNode* curr)
{
  int ans = 0;
  if(curr)
  {
    if(curr->value % 2 == 1)
    {
     ans = 1 + secret(curr->next);
    }
    else 
    {
     ans = 0 + secret(curr->next);
    }
  }
  return ans;
}