#include <stdio.h>

int main()
{	
	char firstLetter = ' ';
	char secondLetter = ' ';
	char thirdLetter = ' ';
	int yearWasBorn = 0;
	int randomNumber = 0;
	int calcForAge = 0;
	//getting the letters for the name
	printf("Enter the first letter:	");
	scanf("%c", &firstLetter);
	getchar();
	printf("Enter the second letter: ");
	scanf("%c", &secondLetter);
	getchar();
	printf("Enter the third letter: ");
	scanf("%c", &thirdLetter);
	getchar();
	
	//getting the year and calculating the age
	printf("\nHey %c%c%c, what year were you born? ", firstLetter, secondLetter, thirdLetter);
	scanf("%d", &yearWasBorn);
	getchar();
	calcForAge = 2024 - yearWasBorn;
	
	//getting the random number
	printf("\nPlease choose any number you would like from 1-100? ");
	scanf("%d", &randomNumber);
	getchar();
	
	//printing
	printf("You are %d years old\n", calcForAge);
	printf(" %d %% %d = %d", calcForAge, randomNumber, calcForAge%randomNumber);
	
	return 0;
}
