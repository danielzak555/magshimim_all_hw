#include <stdio.h>

#define MIN 1

int main()
{
	int theNumber = 0;
	int theOneCanChange = 0;
	int theReversed = 0;
	
	do
	{
		printf("Enter number: ");
		scanf("%d", &theNumber);
		theOneCanChange = theNumber;
		
		if(theNumber < MIN)
			printf("Invalid input! Positive numbers only.\n");
		else
		{
			if(theNumber % 10 == 0)
				theOneCanChange = theOneCanChange / 10;
			while(theOneCanChange >= MIN)
			{
				theReversed = (10 * theReversed) + (theOneCanChange % 10);
				theOneCanChange = theOneCanChange / 10;
			}
			printf("Original number: %d\nAfter reverse: %d\n", theNumber, theReversed);
		}
	}
	while(theNumber < MIN);
	
	return 0;
}
