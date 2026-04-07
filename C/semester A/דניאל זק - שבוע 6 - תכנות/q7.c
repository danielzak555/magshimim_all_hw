#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#define MIN 0
#define MAX 20
#define PLAYAGAIN 'y'

int main()
{
	int theNumber = 0;
	int canChange = 0;
	char Again = ' ';
	bool loopAgain = true;
	
	printf("6");
	do
	{
		printf("Please enter a number between 0 and 20: ");
		scanf("%d", &theNumber);
		canChange = theNumber;
		loopAgain = true;
		if(theNumber >= MIN && theNumber <= MAX)
		{
			do
			{
				switch(canChange)
				{
					case 11:
					case 12:
					case 20:
						printf("%d goes to 6\n", canChange);
						canChange = 6;
						break;
					case 15:
					case 16:
						printf("%d goes to 7\n", canChange);
						canChange = 7;
						break;
					case 13:
					case 14:
					case 18:
					case 19:
						printf("%d goes to 8\n", canChange);
						canChange = 8;
						break;
					case 17:
						printf("%d goes to 9\n", canChange);
						canChange = 9;
						break;
					case 1:
					case 2:
					case 6:
					case 10:
						printf("%d goes to 3\n", canChange);
						canChange = 3;
						break;
					case 3:
					case 7:
					case 8:
						printf("%d goes to 5\n", canChange);
						canChange = 5;
						break;
					case 0:
					case 5:
					case 9:
						printf("%d goes to 4\n", canChange);
						canChange = 4;
						break;
					case 4:
						printf("%d goes to MAGSHIMIM!\n", canChange);
						loopAgain = false;
						break;
				}
				if(loopAgain == false)
				{
					printf("Do you want to continue (y/n)?\n");
					Again = getch();
				}
			}
			while(loopAgain);
		}
	}
	while(theNumber < MIN || theNumber > MAX || Again == 'y');
	
	return 0;
}
