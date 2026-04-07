#include <iostream>
#include "Utils.h"

#include "Stack.h"

#define SIZE_10 10

void reverse(int* nums, unsigned int size){
    unsigned int i = 0;
    Stack* s = new Stack;
    initStack(s);
    for (i = 0; i < size; i++){
        push(s, nums[i]);
    }
    for (i = 0; i < size; i++){
        nums[i] = pop(s);
    }
    cleanStack(s);
    delete s;
}
int* reverse10(){
    int* arr = new int[SIZE_10];
    unsigned int i = 0;
    for(i = 0; i < SIZE_10; i++){
        std::cin >> arr[i];
    }
    reverse(arr, SIZE_10);
    return arr;
}