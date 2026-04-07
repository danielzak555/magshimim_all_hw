#include <stdio.h>

int main()
{
	int numOfTheDay = 18;
	int numOfTheMonth = 5;
	int numOfTheYear = 2009;
	char theNum0 = '0';
	char theNum1 = '1';
	char theNum2 = '2';
	char theNum5 = '5';
	char theNum8 = '8';
	char theNum9 = '9';
	char slashsymbol = '/';
	printf("My birthday is:%d/%d/%d\n", numOfTheDay, numOfTheMonth, numOfTheYear);
	printf("My birthday is:%c%c%c%c%c%c%c%c%c\n", theNum1, theNum8, slashsymbol, theNum5, slashsymbol, theNum2, theNum0, theNum0, theNum9);
	
	return 0;
}
