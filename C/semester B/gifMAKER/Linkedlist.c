#include "Linkedlist.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
the function checkes if the frame is in the list
input: the name of the frame, the head of the list
output: True if yes, False if no
*/
int frameNameExists(FrameNode* head, char* name) 
{
    FrameNode* current = head;
    while (current != NULL) 
    {
        if (strcmp(current->frame->name, name) == 0)
        {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
}

/*
the function finds the length of the list
input: the head of the list
output: the len it self
*/
int getListLength(FrameNode* head) 
{
    int count = 0;
    FrameNode* current = head;
    while (current != NULL) 
    {
        count++;
        current = current->next;
    }
    return count;
}

/*
Function will add a new frame to the end of the linked list.
input: head of the list, the new frame
output: head of the list
*/
FrameNode* addFrame(FrameNode* head, Frame* newFrame) 
{
    FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed!\n");
        return head;
    }
    
    newNode->frame = newFrame;
    newNode->next = NULL;
    
    if (head == NULL) 
    {
        return newNode;
    }
   
    FrameNode* current = head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = newNode;
    
    return head;
}

/*
Function will remove a frame with the given name from the linked list.
input: head of the list, name of frame to remove
output: head of the list after removal
*/
FrameNode* removeFrame(FrameNode* head, char* frameName) 
{
    if (head == NULL) 
    {
        return NULL;
    }
    
    if (strcmp(head->frame->name, frameName) == 0) 
    {
        FrameNode* temp = head;
        head = head->next;
        free(temp->frame->name);
        free(temp->frame->path);
        free(temp->frame);
        free(temp);
        
        return head;
    }

    FrameNode* current = head;
    while (current->next != NULL && strcmp(current->next->frame->name, frameName) != 0) 
    {
        current = current->next;
    }
    
    if (current->next != NULL) 
    {
        FrameNode* temp = current->next;
        current->next = temp->next;
        free(temp->frame->name);
        free(temp->frame->path);
        free(temp->frame);
        free(temp);
    }
    
    return head;
}

/*
Function will change the index (position) of a frame in the linked list.
input: head of the list, name of frame to move, new index
output: head of the list after change
*/
FrameNode* changeFrameIndex(FrameNode* head, char* frameName, int newIndex) 
{
    if (head == NULL || newIndex < 1) 
    {
        return head;
    }
    
    int listLength = getListLength(head);
    if (newIndex > listLength) 
    {
        return head;
    }
    
    FrameNode* prev = NULL;
    FrameNode* current = head;
    FrameNode* frameToMove = NULL;
    
    if (strcmp(head->frame->name, frameName) == 0) 
    {
        frameToMove = head;
        head = head->next;
    }
    else 
    {
        while (current->next != NULL) 
        {
            if (strcmp(current->next->frame->name, frameName) == 0) 
            {
                frameToMove = current->next;
                current->next = frameToMove->next;
                break;
            }
            current = current->next;
        }
    }
    
    if (frameToMove == NULL) 
    {
        return head;
    }
    
    frameToMove->next = NULL;
    
    if (newIndex == 1) 
    {
        frameToMove->next = head;
        return frameToMove;
    }
    
    current = head;
    for (int i = 1; i < newIndex - 1 && current != NULL; i++) 
    {
        current = current->next;
    }
    
    frameToMove->next = current->next;
    current->next = frameToMove;
    
    return head;
}

/*
Function will change the duration of a specific frame.
input: head of the list, name of frame, new duration
output: True if successful, False if frame not found
*/
int changeFrameDuration(FrameNode* head, char* frameName, int newDuration) 
{
    FrameNode* current = head;
    
    while (current != NULL) 
    {
        if (strcmp(current->frame->name, frameName) == 0) 
        {
            current->frame->duration = newDuration;
            return TRUE;
        }
        current = current->next;
    }
    
    return FALSE;
}

/*
Function will change the duration of all frames in the list.
input: head of the list, new duration
output: none
*/
void changeAllFramesDuration(FrameNode* head, int newDuration) 
{
    FrameNode* current = head;
    
    while (current != NULL) 
    {
        current->frame->duration = newDuration;
        current = current->next;
    }
}

/*
Function will print the details of all frames in the list.
input: head of the list
output: none
*/
void listFrames(FrameNode* head) 
{
    if (head == NULL) 
    {
        printf("The gif is empty.\n");
        return;
    }
    
    FrameNode* current = head;
    int index = 1;
    
    printf("\nFrame List:\n");
    
    while (current != NULL) 
    {
        printf("%d. Name: %s, Duration: %u ms, Path: %s\n", index, current->frame->path, current->frame->duration, current->frame->name);
        current = current->next;
        index++;
    }
    printf("\n");
}

/*
Function will play the gif from the list.
input: head of the list
output: none
*/
void playGif(FrameNode* head) 
{
    if (head == NULL) 
    {
        printf("The gif is empty.\n");
        return;
    }
    
    play(head);
}

/*
Function will free all memory allocated for the frames and the list.
input: head of the list
output: none
*/
void freeFrames(FrameNode* head) 
{
    FrameNode* current = head;
    FrameNode* next = NULL;
    
    while (current != NULL) 
    {
        next = current->next;
        
        free(current->frame->name);
        free(current->frame->path);
        free(current->frame);
        free(current);
        
        current = next;
    }
}