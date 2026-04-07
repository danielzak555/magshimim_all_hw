#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node
{
	unsigned int data;
    Node* next;
} Node;

Node* add(Node* head, unsigned int element);
Node* rem(Node* head);

#endif // LINKEDLIST_H