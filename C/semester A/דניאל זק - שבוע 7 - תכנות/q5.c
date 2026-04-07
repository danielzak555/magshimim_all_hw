#include <stdio.h>
#include <conio.h>

int main()
{
	int first = 0;
	int second = 0;
	int mul = 1;
	int divide = 0;
	int i = 1;
	int smallest = 0;
	
	printf("Write the first number\n");
	scanf("%d", &first);
	printf("Write the second number\n");
	scanf("%d", &second);
	if(first >= second)
		smallest = second;
	else
		smallest = first;
	for (i = 1; i <= smallest; i++)
	{
		if(first % i == 0 && second % i == 0)
			divide = i;
	}
	mul = (first * second) / divide;
	printf("The result is %d\n", mul);

	printf("Press any key to continue . . . ");
	getch();
	printf("\n");
	
	return 0;
}
