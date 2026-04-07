#include <stdio.h>

int main()
{
	int sum = 0;
	int chose = 0;
	int i = 1;
	
	printf("Enter number: ");
	scanf("%d", &chose);
	for (i = 1; i < chose; i++)
	{
		if (chose % i == 0)
			sum += i;
	}
	if (sum == chose)
		printf("Yes! The number is perfect");
	if (sum != chose)
		printf("No! The number is not perfect");
	
	return 0;
}
