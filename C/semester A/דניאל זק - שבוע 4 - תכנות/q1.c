#include <stdio.h>

int main()
{
	char firstLetter = 'H';
	char secondLetter = ' ';
	char thirdLetter = ' ';
	int sumOfTheLetters = 0;
	int sumOfThirdLetterAndFirst = 0;
	
	//קולט משתנים מהמשתמש
	printf("Enter the second letter:\n");
	secondLetter = getchar();
	getchar();
	printf("Enter the third letter:\n");
	scanf("%c", &thirdLetter);
	
	sumOfTheLetters = (int)firstLetter + (int)secondLetter + (int)thirdLetter;
	sumOfThirdLetterAndFirst = (int)firstLetter + (int)thirdLetter;
	
	//printing
	printf("the first letter is:%c\nthe first letter + 1:%c\n", firstLetter, firstLetter+1);
	printf("the first letter in number is:%d\n", (int)firstLetter);
	printf("sum of the letters by the ASCII table:%d\n", sumOfTheLetters);
	printf("sum of the third letter and the first by the ASCII table:%d\n", sumOfThirdLetterAndFirst);

	return 0;
}
