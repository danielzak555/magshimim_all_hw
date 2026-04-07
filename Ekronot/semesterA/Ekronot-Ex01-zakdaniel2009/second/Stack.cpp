#include <iostream>
#include "Stack.h"

void push(Stack* s, unsigned int element){
    s->head = add(s->head, element);
    s->count++;
}
int pop(Stack* s){
    if(s->head == nullptr){
        return -1;
    }
    int num = s->head->data;
    s->head = rem(s->head);
    s->count--;
    return num;
}
void initStack(Stack* s){
    s->count = 0;
    s->head = nullptr;
}
void cleanStack(Stack* s){
    while(!isEmpty(s)){
        pop(s);
    }
}
bool isEmpty(Stack* s){
    return s->count == 0;
}
bool isFull(Stack* s){
    return false;
}