#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int i = 0, num = 0, row = 0, j = 0;
    printf("Enter a number: ");
    scanf("%d", &num);
    int* mulTable = (int*)malloc(num * num * sizeof(int));
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < num; j++)
        {
            *(mulTable + ((i * num) + j)) = (i + 1) * (j + 1);
        }
    }

    for(i = 0; i < num * num; i++)
    {
        printf("%4d", *(mulTable + i));// 4d makes space between every number of 4 charecters and makes them in good rows
        if((i + 1) % num == 0)
        {
            printf("\n");
        }
    }

    free(mulTable);

    getchar();
    getchar();
    
    return 0;

}