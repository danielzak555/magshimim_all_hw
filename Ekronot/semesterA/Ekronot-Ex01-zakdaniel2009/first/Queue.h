#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/* a queue contains positive integer values. */
typedef struct Queue
{
	unsigned int* arr;
	unsigned int size;
	int count;
	int front;
	int rear;
	
} Queue;

void initQueue(Queue* q, unsigned int size);
void cleanQueue(Queue* q);

void enqueue(Queue* q, unsigned int newValue);
int dequeue(Queue* q);

bool isEmpty(Queue* s);
bool isFull(Queue* s);

#endif /* QUEUE_H */