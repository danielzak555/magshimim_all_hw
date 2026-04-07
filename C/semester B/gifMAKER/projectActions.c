#include "projectActions.h"

#define MAX_LEN 200

FrameNode* gifLoad(FrameNode* head, char* path)
{
    FILE* gif = fopen(path, "r");
    if (gif == NULL)
        return NULL;

    FrameNode* newHead = NULL;
    FrameNode* tail = NULL;
    int amount = 0;
    char name[MAX_LEN] = {0};
    char framePath[MAX_LEN] = {0};
    int duration = 0;

    if (fscanf(gif, "%d\n", &amount) != 1 || amount <= 0)
    {
        fclose(gif);
        return NULL;
    }

    for (int i = 0; i < amount; i++)
    {
        if (fgets(name, MAX_LEN, gif) == NULL)
        {
            printf("Error reading frame name at line %d\n", i * 3 + 2);
            break;
        }
        name[strcspn(name, "\n")] = '\0';

        if (fgets(framePath, MAX_LEN, gif) == NULL)
        {
            printf("Error reading frame path at line %d\n", i * 3 + 3);
            break;
        }
        framePath[strcspn(framePath, "\n")] = '\0'; 

        if (fscanf(gif, "%d\n", &duration) != 1 || duration <= 0)
        {
            printf("Error reading duration at line %d\n", i * 3 + 4);
            break;
        }

        FrameNode* node = (FrameNode*)malloc(sizeof(FrameNode));
        if (!node)
        {
            printf("Memory allocation failed\n");
            break;
        }

        node->frame = (Frame*)malloc(sizeof(Frame));
        if (!node->frame)
        {
            free(node);
            printf("Memory allocation failed\n");
            break;
        }

        node->frame->name = (char*)malloc(strlen(name) + 1);
        node->frame->path = (char*)malloc(strlen(framePath) + 1);
        if (!node->frame->name || !node->frame->path)
        {
            free(node->frame->name);
            free(node->frame->path);
            free(node->frame);
            free(node);
            printf("Memory allocation failed\n");
            break;
        }

        strcpy(node->frame->name, name);
        strcpy(node->frame->path, framePath);
        node->frame->duration = duration;
        node->next = NULL;

        if (newHead == NULL)
            newHead = node;
        else
            tail->next = node;

        tail = node;
    }

    fclose(gif);
    return newHead;
}


void gifSave(FrameNode* head, char* path)
{
    FILE* file = fopen(path, "w");
    FrameNode* current = head;
    int amount = 0;
    while (current)
    {
        amount++;
        current = current->next;
    }

    fprintf(file, "%d\n", amount);
    current = head;

    while (current)
    {
        fprintf(file, "%s\n", current->frame->name);
        fprintf(file, "%s\n", current->frame->path);
        fprintf(file, "%d\n", current->frame->duration);
        current = current->next;
    }

    fclose(file);
}
