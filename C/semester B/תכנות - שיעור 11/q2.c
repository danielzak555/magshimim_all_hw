#include <stdio.h>

void function(int a, int b);
void newFunction(int a, int b);

int main() 
{
    int a = 0, b = 0;
    printf("Enter a number a\n");
    scanf("%d", &a);
    getchar();
    printf("Enter smaller number b\n");
    scanf("%d", &b);
    getchar();
    
    newFunction(a, b);

    getchar();
    return 0;
}
/*
the function print all numbers between a to b that devisible by b
input: the two number a and b
output: none
efficiancy: O(a-b) -> the nuber of the iterations
*/
void function(int a, int b)
{
    int i = 0;
    for (i = a; i >= b; i--)
    {
        if (i % b == 0)
        {
            printf("%d ", i);
        }
    }
}
/*
the function print all numbers between a to b that devisible by b
input: the two number a and b
output: none
efficiancy: O(a / b)
*/
void newFunction(int a, int b)
{
    int i = 0;
    int max = a / b;
    for (i = 1; i <= max; i++)
    {
        printf("%d ", i * b);
    }
}