#include <stdio.h>

int main()
{	
	char firstLetter = ' ';
	char secondLetter = ' ';
	char thirdLetter = ' ';
	
	printf("Enter the first letter:	");
	scanf("%c", &firstLetter);
	getchar();
	printf("Enter the second letter: ");
	scanf("%c", &secondLetter);
	getchar();
	printf("Enter the third letter: ");
	scanf("%c", &thirdLetter);
	getchar();
	
	printf("the name is	%c%c%c", firstLetter, secondLetter, thirdLetter);
	
	return 0;
}
