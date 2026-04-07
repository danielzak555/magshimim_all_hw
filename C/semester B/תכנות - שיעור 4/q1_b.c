#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int amount = 0;
    printf("enter the amount of memory: ");
    scanf("%d", &amount);
    int* memory = (int*)malloc(sizeof(int) * amount);
    if (memory == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
	getchar();
}
