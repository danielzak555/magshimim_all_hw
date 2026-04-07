#include <stdio.h>

#define MIN 1
#define PLAYAGAIN 'y'

int main() 
{
    int theNumber = 0;
	int i = 0;
	char playAgain = ' ';

    do {
        printf("Enter number: ");
        scanf("%d", &theNumber);

        if (theNumber < MIN) 
		{
            printf("Invalid input!\n");
        }
		else
		{
			for (i = 1; i <= theNumber; i++) 
			{
				printf("%d ", i * i);
				if (i == theNumber)
					printf("\n");
			}
			printf("Would you like to try again?\n");
			getchar();
			playAgain = getchar();
		}
		
    } 
	while (theNumber < MIN || PLAYAGAIN == playAgain);

    return 0;
}
