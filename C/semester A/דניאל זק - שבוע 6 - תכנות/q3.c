#include <stdio.h>

#define MAX_MUL 10

int main(void)
{
	int numberWeMultiply = 1; 
	int multiplyBy = 0;
	
	printf("Daniel Presents: The Board of Multiplication!\n\n");
	
	// Main loop
	for(numberWeMultiply = 1; numberWeMultiply <= 10; numberWeMultiply++)
	{	
		// Inner loop
		for(multiplyBy = 1; multiplyBy <= 10; multiplyBy++)
		{
			printf("%d ", numberWeMultiply * multiplyBy); // Printing multiplication
			if(multiplyBy == MAX_MUL)
			{
				printf("\n"); // newline
			}
		}
		
	} // End of main loop
	
	// returning 0
	return 0;
}
