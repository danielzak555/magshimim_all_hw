#include <iostream>
#include "Queue.h"

void initQueue(Queue* q, unsigned int size){
    q->arr = new unsigned int [size];
    q->size = size;
    q->count = 0;
    q->front = 0;
    q->rear = 0;
}

void cleanQueue(Queue* q){
    delete[] q->arr;
    q->arr = NULL;
    q->size = 0;
    q->count = 0;
    q->front = 0;
    q->rear = 0;
}

void enqueue(Queue* q, unsigned int newValue){
    if(isFull(q)){
        return;
    }

    q->arr[q->rear] = newValue;
    q->count++;
    q->rear = (q->rear + 1) % q->size;
}
int dequeue(Queue* q){
    if (isEmpty(q)){
        return -1;
    }

    unsigned int value = q->arr[q->front];
    q->count--;
    q->front = (q->front + 1) % q->size;
    return value;
}

bool isEmpty(Queue* s){
    return s->count == 0;
}

bool isFull(Queue* s){
    return s->count == s->size;
}