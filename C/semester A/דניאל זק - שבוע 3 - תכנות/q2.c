#include <stdio.h>

int main()
{
	char firstLetter = 'A';
	char lastLetter = 'Z';
	int numOfLetters = (int)lastLetter - (int)firstLetter + 1;
	printf("the first big letter in the abc:%c\nthe last big letter in the abc:%c\n", firstLetter, lastLetter);
	printf("the number of the letters in the abc:%d\n", numOfLetters);
	
	return 0;
}
