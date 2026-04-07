#include <stdio.h>

#define MAX 9
#define MIN 1

int main()
{
	int theNumberWePrinting = 0; 
	int numberOfPrints = 0;
	int numOfLines = 0;
	do
	{
		printf("Enter number: ");
		scanf("%d", &numOfLines);
		
		if(numOfLines < MIN || numOfLines > MAX)
			printf("Invalid input! 1-9 only\n");
		
		else
		{
			for(theNumberWePrinting = 1; theNumberWePrinting <= numOfLines; theNumberWePrinting++)
			{	
				for(numberOfPrints = 1; numberOfPrints <= theNumberWePrinting; numberOfPrints++)
				{
					printf("%d ", theNumberWePrinting);
					if(numberOfPrints == theNumberWePrinting)
					{
						printf("\n");
					}
				}
				
			}
		}
	}
	while(numOfLines < MIN || numOfLines > MAX);
	return 0;
}
