/*********************************
* Class: MAGSHIMIM C1			 *
* Week 7           				 *
**********************************/

#include <stdio.h>
#include <stdlib.h>

#define LOWER 0
#define UPPER 172486
/*
Bug Report: 
1. move int num = 0; to the head of the fun
2.change the name of the usage fun to a name more meaningful
3.add the printf of what we need to input if we put invalid one before ---> (printf("Please enter a number between %d - %d: \n", LOWER, UPPER))
*/
void welcome(void);
void explain(void);
void getNumber(void);
void printTwice(int number);

int main(void)
{
	welcome();
	return 0;
}

/*
This function prints "welcome".
input: none
output: none
*/
void welcome(void)
{
	printf("Welcome to my cool program!\n");
	explain();
}

/*
This function prints what the program is for.
input: none
output: none
*/
void explain(void)
{
	printf("My program gets a number from you - and prints it twice in a row!\n");
	getNumber();
}

/*
The function gets a number.
input: none
output: none
*/
void getNumber(void)
{
	int number = 0;// put this row in the top of the fun
	printf("Please enter a number between %d - %d: \n", LOWER, UPPER);
	scanf("%d", &number);
	while(number < LOWER || number > UPPER)
	{
		printf("Invalid choice!\n");
		printf("Please enter a number between %d - %d: \n", LOWER, UPPER);
		scanf("%d", &number);
	}
	printTwice(number);
}


/*
Prints the number twice. 
input: the number we got from the user.
output: none
*/
void printTwice(int number)
{
	printf("The number twice in a row: %d%d", number, number);
}
