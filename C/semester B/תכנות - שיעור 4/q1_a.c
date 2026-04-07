#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* num = (int*)malloc(sizeof(int));
    if (num == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    free(num);
    getchar();
}
