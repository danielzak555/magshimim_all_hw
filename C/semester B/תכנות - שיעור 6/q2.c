#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50
#define SIZE_OF_CHAR_POINTER 4
#define SIZE_OF_CHAR 1

void getName(char name[], int len);

int main()
{
	int friends = 0, i = 0, nameLen = 0, j = 0, totalAllocated = 0;
    char* temp = NULL;
    char name[MAX_LEN] = {0};
    char** names = {0};
    printf("Enter number of friends: ");
    scanf("%d", &friends);
    getchar();
    names = (char**)malloc(friends * sizeof(char*));
    totalAllocated += friends * SIZE_OF_CHAR_POINTER;

    if (names == NULL) 
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for(i = 0; i < friends; i++)
    {
        printf("Enter name of friend %d: ", i + 1);
        getName(name, MAX_LEN);
        nameLen = strlen(name);
        names[i] = (char*)malloc((nameLen + 1) * sizeof(char));
        totalAllocated += (nameLen + 1) * SIZE_OF_CHAR;

        if (names[i] == NULL) 
        {
            printf("Memory allocation failed!\n");
            return 1;
        }
        strcpy(names[i], name);

    }

    for (i = 0; i < friends - 1; i++) 
    {
        for (j = 0; j < friends - i - 1; j++) 
        {
            if (strcmp(names[j], names[j + 1]) > 0) 
            {
                temp = names[j];
                names[j] = names[j + 1];
                names[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < friends; i++) 
    {
        printf("Friend %d: %s\n", i + 1, names[i]);
    }
    printf("Total allocated: %d", totalAllocated);
    printf("\n");

    for(i = 0; i < friends; i++)
    {
        free(names[i]);
    }
    free(names);

    getchar();

	return 0;
}
/*
this function gets a name from the user and removes the \n
input: arr for the name, len of arr
output: none
*/
void getName(char name[], int len)
{
    fgets(name, len, stdin);
    name[strcspn(name, "\n")] = 0;
}

