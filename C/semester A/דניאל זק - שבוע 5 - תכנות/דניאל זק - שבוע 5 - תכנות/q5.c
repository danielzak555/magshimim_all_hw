#include <stdio.h>
 
int main()
{
	float price = 0;
	int slices = 0;
	printf("please enter the price: ");
	scanf("%f", &price);
	printf("please enter the amount of slices: ");
	scanf("%d", &slices);
	
	if (price < 50 && slices >= 3)
	{
		printf("You should buy this pizza\n");
	}
	else if (slices > 8)
	{
		printf("You should buy this pizza\n");
	}
	else 
	{
		printf("This pizza it too expensive\n");
	}
	return 0;
}
