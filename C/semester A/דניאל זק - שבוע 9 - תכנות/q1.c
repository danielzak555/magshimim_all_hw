#include <stdio.h>

#define MIN 0
#define MAX 2

void printJoke(int sides);
int userChoise(void);
void welcome(void);

int main()
{
	int choise = 0;
	welcome();
	choise = userChoise();
	printJoke(choise);
	printf("\nPress any key to continue . . . ");
	getchar();
	printf("\n");
	
	return 0;
}
/*the function print the joke by the type that was chosen
input: choise - the type of the joke
output: none
*/

void printJoke(int choise)
{
	printf("\nYour Joke:\n----------\n");
	if(MIN <= choise && MAX >= choise)
	{
		if(MIN == choise)
			printf("I'd tell them a UDP joke but there's no guarantee that they would get it.\n");
		else if(MAX == choise)
			printf("I'm going to stand outside. So if anyone asks, I'm outstanding.\n");
		else
			printf("Who's there?\nFigs.\nFigs who?\nFigs the doorbell, it's not working!\n");
	}
	else
		printf("A priest, a rabbi and a duck walk into a bar.\nThe bartender says: Is this some kind of a joke?!\n");
}

/*the function print the joke menu and gets the type of joke
input: none
output: the type of the joke that was chosen
*/

int userChoise(void)
{
	int type = 0;
	printf("What kind of a joke would you like?\nProgramming joke - 0\nKnock-knock joke - 1\nWordplay joke - 2\n");
	scanf("%d", &type);
	getchar();
	
	return type;
}

/*the function print the welcome line
input: none
output: none
*/

void welcome(void)
{
	printf("Welcome to the Comedy Store!\n");
}
