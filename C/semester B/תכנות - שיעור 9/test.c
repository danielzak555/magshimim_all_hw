#include <stdio.h>

int recursiveTriangle(int n);


int recursiveTriangle(int n)
{
    int i = 0;
    if(n == 0)
    {
        i = 1;
    }
    else{
        i = n * recursiveTriangle(n - 1);
    }
    return i;
}

int main(void)
{
    int num = 0, i = 0;
    scanf("%d", &num);
    i = recursiveTriangle(num);
    printf("%d", i);

    return 0;
}