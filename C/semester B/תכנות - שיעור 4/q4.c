#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

float avg(int *arr, int len);
void changeAnswer(int *arr, int len);
int* addAnswers(int *arr, int len, int* newlen);
void printAnswers(int *arr, int len);
bool check(int num);

#define MIN 0
#define AVRAGE 1
#define CHANGE 2
#define ADD 3
#define PRINT 4
#define EXIT 5
#define MAX 6

int main(void)
{
    int people = 0, i = 0, ans = 0, choise = 0;
    float average = 0;
    printf("Enter number of responders: ");
    scanf("%d", &people);
    int *arr = (int *)malloc(sizeof(int) * people);
    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (i = 0; i < people; i++)
    {
        printf("Enter score %d: ", i+1);
        scanf("%d", &ans);
        while (check(ans) == false)
        {
            printf("Invalid score. 1-5 only. Try again: ");
            scanf("%d", &ans);
        }
        *(arr + i) = ans;
    }

    do
    {
        printf("1 - Calculate average\n2 - Change a score\n3 - Add responders and their scores\n4 - Print scores distribution\n5 - Exit\nChoose option: ");
        scanf("%d", &choise);
        while (check(choise) == false)
        {
            printf("Invalid score. 1-5 only. Try again: ");
            scanf("%d", &choise);
        }

        switch (choise)
        {
        case AVRAGE:
            average = avg(arr, people);
            printf("The score average is: %.2f\n", average);
            break;
        case CHANGE:
            changeAnswer(arr, people);
            break;
        case ADD:
            arr = addAnswers(arr, people, &people);
            break;
        case PRINT:
            printAnswers(arr, people);
            break;
        }

    } while (choise != EXIT);

    free(arr);
    getchar();
    getchar();
    return 0;
}

/*
the function will calc the avg
input: pointer to arr, the len
output: the avg
*/
float avg(int *arr, int len)
{
    int i = 0;
    float sum = 0;
    for (i = 0; i < len; i++)
    {
        sum += *(arr + i);
    }
    return (sum / len);
}
/*
the function change the score of one of the responders
input: pointer to arr, the len
output: none
*/
void changeAnswer(int *arr, int len)
{
    int change = 0, new = 0;
    printf("Which score would you like to change? 1-%d: ", len);
    scanf("%d", &change);
    while (change < 1 || change > len)
    {
        printf("Invalid score. Try again: ");
        scanf("%d", &change);
    }
    printf("Enter new score: ");
    scanf("%d", &new);
    while (check(new) == false)
    {
        printf("Invalid score. 1-5 only. Try again: ");
        scanf("%d", &new);
    }
    *(arr + change - 1) = new;
}
/*
the function will add new responders and their scores
input: pointer to arr, the len
output: the new arr
*/
int* addAnswers(int *arr, int len, int *newlen)
{
    int new = 0, i = 0;
    int* temp = NULL;
    printf("How many new responders? ");
    scanf("%d", &new);
    temp = (int *)realloc(arr, sizeof(int) * (len + new));
    if (temp == NULL)
    {
        printf("realloc failed.\n");
        *newlen = len;
        return arr;
    }
    arr = temp;
    for (i = len; i < len + new; i++)
    {
        printf("Enter score %d: ", i+1);
        scanf("%d", &arr[i]);
        while (check(*(arr + i)) == false)
        {
            printf("Invalid score. 1-5 only. Try again: ");
            scanf("%d", &arr[i]);
        }
    }
    *newlen = len + new;
    return arr;
}
/*
the func will print the distribution of the scores
input: pointer to arr, the len
output: none
*/
void printAnswers(int *arr, int len)
{
    int i = 0, count[6] = {0};
    for (i = 0; i < len; i++)
    {
        count[arr[i]]++;
    }
    for (i = 1; i <= 5; i++)
    {
        printf("%d - %d\n", i, count[i]);
    }
}
/*
the function checks if the number is valid
input:the number to check
output: true if good, else false
*/
bool check(int num)
{
    if (num <= MIN || num >= MAX)
    {
        return false;
    }
    return true;

}
