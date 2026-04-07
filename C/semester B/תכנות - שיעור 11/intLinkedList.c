#include <stdio.h>
#include <stdlib.h>

typedef struct IntNode
{
	int val;
	struct IntNode *next;
} IntNode;

void printList(IntNode *list);
void freeList(IntNode *list);

int main(void)
{
	IntNode *list = NULL;
	printList(list);

	// TODO: HW

	getchar();
}

void printList(IntNode *list)
{
	if (list)
	{
		printf("%d  ", list->val);
		printList(list->next);
	}
	else
	{
		printf("\n");
	}
}

void freeList(IntNode *list)
{
}

IntNode *concatenate(IntNode *list1, IntNode *list2)
{
	IntNode *current1 = list1;
	IntNode *previus1 = NULL;
	IntNode *current2 = list2;
	IntNode *previus2 = NULL;

	if (list1 == NULL)
	{
		return list2;
	}
	if (list2 == NULL)
	{
		return list1;
	}
	
	while (current1 != NULL && current2 != NULL)
	{
		previus1 = current1;
		previus2 = current2;
		current1 = current1->next;
		current2 = current2->next;
	}

	if (current1 == NULL)
	{
		previus1->next = list2;
		return list1;
	}
	else
	{
		previus2->next = list1;
		return list2;
	}
}