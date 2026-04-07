#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPalindrome(char str[], int beg, int end);

#define MAX_LEN 50

int main()
{
    char str[MAX_LEN] = {0};
    printf("Enter string: ");
    fgets(str, MAX_LEN, stdin);
    str[strcspn(str, "\n")] = 0;
    int start = 0;
    bool isPalindrom = isPalindrome(str, start, strlen(str) - 1);
    if (isPalindrom)
    {
        printf("Yes, it's a palindrome!\n");
    }
    else
    {
        printf("Not a palindrome!\n");
    }
    getchar();
    return 0;
}

/*
the recursive func check if the str is a palindrome
input: str - arr or char, beg - the index of first letter to check, end - the index of second letter to check
output: if tto letters equal or not
*/
bool isPalindrome(char str[], int beg, int end)
{
    bool isPal = true;
    printf("%d %d\n", beg, end);
    printf("%c %c\n", str[beg], str[end]);
    if(beg >= end)
    {
        return isPal;
    }
    else if(str[beg] == str[end])
    {
        isPal = isPalindrome(str, beg + 1, end - 1);
    }
    else
    {
        isPal = false;
    }
    return isPal;
}
