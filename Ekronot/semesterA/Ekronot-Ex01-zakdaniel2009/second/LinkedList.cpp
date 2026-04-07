#include <iostream>
#include "LinkedList.h"

Node* add(Node* head, unsigned int element){
    Node* newNode = new Node();
    newNode->data = element;
    newNode->next = head;
    return newNode;
}
Node* rem(Node* head){
    if (head == nullptr){
        return nullptr;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}