#include "linkedList.h"
#include "view.h"
#include "projectActions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 200
#define MAX_OP 8
#define MIN_OP 0
#define MIN_DUR_OR_LOC 1

int fileExists(char* path);
int getMovieLength(FrameNode* head);
int isFrameNameTaken(FrameNode* head, char* name);
void printMenu();

enum option {quit = 0, add, frameRemove, location, oneDuration, allDuration, frameList, gifPlay, saveTheGif};

int main()
{
    FrameNode* gifList = NULL;
    int choice = 0;
    char frameName[MAX_STR_LEN] = {0};
    char framePath[MAX_STR_LEN] = {0};
    char filePath[MAX_STR_LEN] = {0};
    int duration = 0;
    int newPosition = 0;

    printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
    printf("0. create new project\n1. load existing project\n");

    while (scanf("%d", &choice) != 1 || (choice < 0 || choice > 1)) {
        printf("Invalid choice. try again: ");
        while (getchar() != '\n'); // clear buffer
    }
    while (getchar() != '\n'); // clear newline

    if (choice == 1)
    {
        printf("enter file path: ");
        while (fgets(filePath, MAX_STR_LEN, stdin) == NULL || filePath[0] == '\n')
        {
            printf("Error reading input! try again: ");
        }

        filePath[strcspn(filePath, "\n")] = '\0'; // remove newline

        while (!fileExists(filePath))
        {
            printf("File does not exist! try again: ");
            if (fgets(filePath, MAX_STR_LEN, stdin) == NULL)
            {
                printf("Error reading input!\n");
                continue;
            }
            filePath[strcspn(filePath, "\n")] = '\0';
        }

        gifList = gifLoad(gifList, filePath);
        if (gifList == NULL)
        {
            printf("error loading file, creating new one\n");
        }
    }

    do
    {
        printMenu();
        while (scanf("%d", &choice) != 1 || choice < MIN_OP || choice > MAX_OP) {
            printf("try again: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        switch (choice)
        {
			case quit:
			{
				printf("Goodbye!\n");
				break;
			}

			case add:
			{
				printf("Add New Frame\n");
				
				printf("Enter frame path: ");

				fgets(framePath, MAX_STR_LEN, stdin);

				if (framePath == NULL)
				{
					printf("Error reading input!\n");
					break;
				}

				framePath[strcspn(framePath, "\n")] = '\0';
				
				if (!fileExists(framePath))
				{
					printf("Error: File '%s' does not exist!\n", framePath);
					break;
				}
				
				printf("Enter frame duration: ");
				scanf("%d", &duration);

				while (duration < MIN_DUR_OR_LOC)
				{
					printf("try again: ");
					scanf("%d", &duration);
				}
				
				getchar();
				
				printf("Enter frame name: ");
				
				fgets(frameName, MAX_STR_LEN, stdin);

				if (frameName == NULL)
				{
					printf("Error reading input!\n");
					break;
				}

				frameName[strcspn(frameName, "\n")] = '\0';
				
				if (strlen(frameName) == 0)
				{
					printf("Frame name cannot be empty!\n");
					break;
				}

				while (isFrameNameTaken(gifList, frameName))
				{
					printf("Frame name '%s' already exists!\n", frameName);
					printf("Enter a different name: ");
					fgets(frameName, MAX_STR_LEN, stdin);
					if (frameName == NULL)
					{
						printf("Error reading input!\n");
						break;
					}

					frameName[strcspn(frameName, "\n")] = '\0';
					
					if (strlen(frameName) == 0)
					{
						printf("Frame name cannot be empty!\n");
						break;
					}
				}
				
				Frame* newFrame = (Frame*)malloc(sizeof(Frame));
				if (newFrame == NULL)
				{
					printf("Memory allocation failed!\n");
					break;
				}
				
				newFrame->name = (char*)malloc(strlen(frameName) + 1);
				newFrame->path = (char*)malloc(strlen(framePath) + 1);
				
				if (newFrame->name == NULL || newFrame->path == NULL)
				{
					printf("Memory allocation failed!\n");
					free(newFrame->name);
					free(newFrame->path);
					free(newFrame);
					break;
				}
				
				strcpy(newFrame->name, frameName);
				strcpy(newFrame->path, framePath);
				newFrame->duration = duration;
				
				gifList = addFrame(gifList, newFrame);
				printf("Frame '%s' added successfully!\n", frameName);
				break;
			}
			
			case frameRemove:
			{
				printf("Remove Frame\n");
				
				if (gifList == NULL)
				{
					printf("The movie is empty!\n");
					break;
				}
				
				printf("Enter frame name to remove: ");

				fgets(frameName, MAX_STR_LEN, stdin);
				if (frameName == NULL)
				{
					printf("Error reading input!\n");
					break;
				}

				frameName[strcspn(frameName, "\n")] = '\0';
				
				if (!isFrameNameTaken(gifList, frameName))
				{
					printf("Frame '%s' not found!\n", frameName);
				}
				
				else
				{
					gifList = removeFrame(gifList, frameName);
					printf("Frame '%s' removed successfully!\n", frameName);
				}
				break;
			}
			
			case location:
			{
				printf("Change Frame Position\n");
				
				if (gifList == NULL)
				{
					printf("The movie is empty!\n");
					break;
				}
				
				printf("Enter frame name: ");

				fgets(frameName, MAX_STR_LEN, stdin);
				if (frameName == NULL)
				{
					printf("Error reading input!\n");
					break;
				}

				frameName[strcspn(frameName, "\n")] = '\0';
				
				if (!isFrameNameTaken(gifList, frameName))
				{
					printf("Frame '%s' not found!\n", frameName);
					break;
				}
				
				int movieLength = getMovieLength(gifList);
				printf("Enter new position (1-%d): ", movieLength);

				scanf("%d", &newPosition);
				while (newPosition < MIN_DUR_OR_LOC || newPosition > movieLength)
				{
					printf("try again: ");
					scanf("%d", &newPosition);
					break;
				}
				getchar();
				
				gifList = changeFrameIndex(gifList, frameName, newPosition);
				printf("Frame '%s' moved to position %d successfully!\n", frameName, newPosition);
				break;
			}
			
			case oneDuration:
			{
				printf("Change Frame Duration\n");
				
				if (gifList == NULL)
				{
					printf("The movie is empty!\n");
					break;
				}
				
				printf("Enter frame name: ");
				fgets(frameName, MAX_STR_LEN, stdin);
				if (frameName == NULL)
				{
					printf("Error reading input!\n");
					break;
				}
				frameName[strcspn(frameName, "\n")] = '\0';
				
				printf("Enter new duration: ");

				scanf("%d", &duration);
				if (duration < MIN_DUR_OR_LOC)
				{
					printf("Invalid duration!\ntry again: ");
					scanf("%d", &duration);
					break;
				}
				getchar();
				
				if (changeFrameDuration(gifList, frameName, duration))
				{
					printf("Frame '%s' duration changed to %d ms successfully!\n", frameName, duration);
				}
				
				else
				{
					printf("Frame '%s' not found!\n", frameName);
				}
				break;
			}
			
			case allDuration:
			{
				printf("Change All Frames Duration\n");
				
				if (gifList == NULL)
				{
					printf("The movie is empty!\n");
					break;
				}
				
				printf("Enter new duration for all frames: ");

				scanf("%d", &duration);
				if (duration < MIN_DUR_OR_LOC)
				{
					printf("Error: Invalid duration!\ntry again: ");
					scanf("%d", &duration);
					break;
				}
				getchar();
				
				changeAllFramesDuration(gifList, duration);
				printf("All frames duration changed to %d ms successfully!\n", duration);
				break;
			}
			
			case frameList:
			{
				printf("Frame List\n");
				listFrames(gifList);
				break;
			}
				
			case gifPlay:
			{
				printf("Play Movie\n");
				if (gifList == NULL)
				{
					printf("The movie is empty!\n");
				}
				
				else
				{
					playGif(gifList);
				}
				break;
			}

			case saveTheGif:
            {
                printf("enter the path to where to save (with file name): ");
                while (fgets(filePath, MAX_STR_LEN, stdin) == NULL || filePath[0] == '\n') {
                    printf("Error reading input! try again: ");
                }
                filePath[strcspn(filePath, "\n")] = '\0';

                gifSave(gifList, filePath);
                break;
            }

        }

    } while (choice != 0);

    freeFrames(gifList);
    return 0;
}

/*
Checks if a file exists at the given path.
input: path - A string representing the file path.
output: TRUE if the file exists, FALSE otherwise.
*/
int fileExists(char* path)
{
	FILE* file = fopen(path, "r");
	if (file)
	{
		fclose(file);
		return TRUE;
	}
	return FALSE;
}

/*
Checks if a frame name is already used in the linked list.
input: head - Pointer to the head of the FrameNode list.
input: name - The frame name to check.
output: TRUE if the name is taken, FALSE otherwise.
*/
int isFrameNameTaken(FrameNode* head, char* name)
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
Calculates the total number of frames in the linked list.
input: head - Pointer to the head of the FrameNode list.
output: The number of frames in the list.
*/
int getMovieLength(FrameNode* head)
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
Prints the main menu options to the console.
input: None
output: None
*/
void printMenu()
{
	printf("\nMovie Editor Menu\n");
	printf("0. Exit\n");
	printf("1. Add new frame\n");
	printf("2. Remove frame\n");
	printf("3. Change frame position\n");
	printf("4. Change frame duration\n");
	printf("5. Change all frames duration\n");
	printf("6. List frames\n");
	printf("7. Play movie\n");
	printf("8. save the movie\n");
	printf("Enter your choice: ");
}