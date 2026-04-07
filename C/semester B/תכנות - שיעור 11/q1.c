#include <stdio.h>
#include <math.h>

void sqrtBelow(int n);

int main() 
{
    int n = 0;
    printf("Enter a number: ");
    scanf("%d", &n);
    getchar();
    
    sqrtBelow(n);

    getchar();
    return 0;
}
/*
the function prints all perfect sqrt below the number
input: the number
output: none
efficiency: O(n^0.5) -> its just the number of the itterations
*/
void sqrtBelow(int n)
{
    int max_squares = (int)sqrt(n);
    int i = 0;
    
    printf("All squares less than %d:\n", n);
    for (int i = 1; i <= max_squares; i++) 
    {
        printf("%d ", i * i);
    }
    printf("\n");
}