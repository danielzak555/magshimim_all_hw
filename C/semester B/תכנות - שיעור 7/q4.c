#include <stdio.h>
#include <string.h>

void myFGets(char *str, int size);
int menu(void);
int countString(char* path);

#define ARGC_AMOUNT 2
#define PATH 2
#define MAX_SIZE 50

enum choise {search = 1, change, copy, exit};

int main(int argc, char* argv[])
{
    FILE *file = NULL;
    int choise = 0;

    if (argc != ARGC_AMOUNT)
    {
        printf("Usage: %s <csv file path>\n", argv[0]);
        return 1;
    }
    do
    {
        choise = menu();
        switch (choise)
        {
            case search:
                if(countString(argv[1]) == 1)
                {
                    return 1;
                }
                break;
            case change:
                break;
            case copy:
                break;
            case exit:
                printf("Goodbye\n");
                getchar();
        }
    }while(choise != exit);


    return 0;
}

/*
Displays a menu to the user and gets their choice.
input: void
output: the user's choice (an integer corresponding to a menu option)
*/
int menu(void)
{
    int choise = 0;
    printf("Please enter your choice:\n1 - Search a term in the document.\n2 - change a value in a specific place.\n3 - copy a value from one place to another\n4 - Exit\n");
    scanf("%d", &choise);
    getchar();
    while (choise > exit || choise < search)
    {
        printf("Try again.\n");
        printf("Please enter your choice:\n1 - Search a term in the document\n.2 - change a value in a specific place\n.3 - copy a value from one place to another\n4 - Exit");
        scanf("%d", &choise);
        getchar();
        getchar();
    }
    return choise;
}

/*
Counts the occurrences of a string entered by the user in a file.
input: path: A pointer to a null-terminated string representing the path to the file.
output:0 if the string is found and counted successfully, 1 if there is an error opening the file.
*/
int countString(char* path)
{
    FILE *file = NULL;
    char find[MAX_SIZE] = {0};
    char ch = ' ';
    char element[MAX_SIZE] = {0};
    int i = 0, count = 0;

    file = fopen(path, "r");
    if(file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    myFGets(find, MAX_SIZE);

    while ((ch = (char)fgetc(file)) != EOF)
    {
        if(ch != ',' && ch != '\n')
        {
            element[i] = ch;
            i++;
        }
        else
        {
            if(strcmp(find, element) == 0)
            {
                count++;
            }
            for(i = 0; i < MAX_SIZE; i++)
            {
                element[i] = 0;
            }
            i = 0;
        }
    }
    if(strcmp(find, element) == 0)
    {
        count++;
    }
    printf("Value appears %d times\n", count);

    fclose(file);
    return 0;
}

/*
Reads a line of text from standard input, up to a specified size.
It replaces the trailing newline character with a null terminator.
input: str: A pointer to a character array where the input string will be stored, size: The maximum number of characters to read (including the null terminator).
output: void
*/
void myFGets(char *str, int size)
{
    printf("Enter string to search: ");
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}