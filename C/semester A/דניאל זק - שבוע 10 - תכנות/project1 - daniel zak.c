//first project
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

void welcome(void);
void getModeSetRound(void);
void genCode(void);
void getAndCheck(void);
void checkHits(int one, int two, int three, int four);

#define MAXNUM 6
#define MINNUM 1
#define MAXRAND 6543
#define MINRAND 1234
#define ZEROASCII 48
#define MAXROUND 25
#define MINROUND 5

enum levels{easy = 1, moderate, hard, crazy};

int mode = 0;
int rounds = 0;
int randNum = 0;

int main()
{
	int again = 2;
	char signal = ' ';
	do
	{
		again = 2;
		welcome();
		getModeSetRound();
		genCode();
		getAndCheck();
		getchar();
		while(again == 2)
		{
			printf("Would you like to play again? (y/n): ");
			scanf("%c", &signal);
			printf("\n");
			if(signal == 'y')
				again = 1;
			else if(signal == 'n')
			{	
				again = 0;
				printf("Bye Bye!\nPress any key to continue . . . ");
				getch();
			}
		}
	}
	while(again == 1);
}	

/*the fun prints the welcome text
input: none
output: none
*/
void welcome(void)
{
	printf("Welcome to MAGSHIMIM CODE-BREAKER!!!\n\n");
	printf("A secret password was chosen to protect the credit card of Pancratius,\nthe descendant of Antiochus.");
	printf("Your mission is to stop Pancratius by revealing his secret password.\n\n");
	printf("The rules are as follows:\n");
	printf("1. In each round you try to guess the secret password (4 distinct digits)\n");
	printf("2. After every guess you'll receive two hints about the password\n   HITS:   The number of digits in your guess which were exactly right.\n   MISSES: The number of digits in your guess which belongs to\n           the password but were miss-placed.\n");
	printf("3. If you'll fail to guess the password after a certain number of rounds\n  Pancratius will buy all the gifts for Hanukkah!!!\n\n");                                                               
}

/*this function print the modes and gets one
input: none
output: the mode of game
*/
void getModeSetRound(void)
{
	bool fine = false;
	printf("Please choose the game level:\n1 - Easy (20 rounds)\n2 - Moderate (15 rounds)\n3 - Hard (10 rounds)\n4 - Crazy (random number of rounds 5-25)\n");
	do
	{
		printf("Make a choice: ");
		scanf("%d", &mode);
		switch(mode)
		{
			case easy:
				rounds = 20;
				fine = true;
				break;
			case moderate:
				rounds = 15;
				fine = true;
				break;
			case hard:
				rounds = 10;
				fine = true;
				break;
			case crazy:
				srand(time(NULL));
				rounds = rand() % (MAXROUND - MINROUND + 1) + MINROUND;
				fine = true;
				break;
		}
	}
	while(!fine);
}

/*this fun will gen valid code that we need to guess
input: none
output: none
*/
void genCode(void)
{
	int first = 0, second = 0, third = 0, fourth = 0;
	int ok = false;
	srand(time(NULL));
	do
	{
		randNum = rand() % (MAXRAND - MINRAND + 1) + MINRAND;
		first = randNum / 1000;
		second = (randNum / 100) % 10;
		third = (randNum / 10) % 10;
		fourth = randNum % 10;
		if(MINNUM <= first && MINNUM <= second && MINNUM <= third && MINNUM <= fourth && MAXNUM >= first && MAXNUM >= second && MAXNUM >= third && MAXNUM >= fourth)
		{	
			if(first != second && first != third && first != fourth && second != third && second != fourth && third != fourth)
				ok = true;
		}
	}
	while(!ok);
}

/*this fun will get the guess from the user
input: none
output: none
*/
void getAndCheck(void)
{
	int one = 0, two = 0, three = 0, four = 0, count = 0, theGuess = 0;
	bool good = false, won = false;
	do	
	{
		if(rounds > 0)
		{
			printf("Write your guess (only 1-6, no ENTER is needed)\n");
			if(mode == 4)
				printf("CRAZY MODE!!!\n");
			else
				printf("%d guesses left\n", rounds);
			one = getch() - ZEROASCII;
			printf("%d", one);
			two = getch() - ZEROASCII;
			printf("%d", two);
			three = getch() - ZEROASCII;
			printf("%d", three);
			four = getch() - ZEROASCII;
			printf("%d\n", four);
			if(MINNUM <= one && MINNUM <= two &&  MINNUM <= three && MINNUM <= four && MAXNUM >= one && MAXNUM >= two && MAXNUM >= three && MAXNUM >= four)
			{
				if(one != two && one != three && one != four && two != three && two != four && three != four)
				{
					good = true;
					rounds--;
					count++;
					theGuess = (one * 1000) + (two * 100) + (three * 10) + four;
					if(randNum == theGuess)
					{
						won = true;
						printf("4 HITS YOU WON!!!\n");
						printf("It took you only %d guesses, you are a professional code breaker!\n", count);
						printf("       _______       \n");
						printf("      |       |      \n");
						printf("     /         \\     \n");
						printf("    / You're    \\    \n");
						printf("   |   the Best! |   \n");
						printf("    \\           /    \n");
						printf("     \\_________/     \n");
						printf("         |||          \n");
						printf("         |||          \n");
						printf("         |||          \n");
						printf("     ____|||____      \n");
						printf("    |          |      \n");
						printf("    |__________|      \n");
					}
					else
						checkHits(one, two, three, four);
				}
				else
					printf("Same numbers not allowed, try again!\n");
			}
			else
				printf("Only 1-6 are allowed, try again!\n");
		}
		else
		{	
			printf("OOOOHHHH!!! Pancratius won and bought all of Hanukkah's gifts.\nNothing left for you...\nThe secret password was %d\n", randNum);
			break;
		}
	}
	while(good == false || won == false);
}

/*will check how much hits and misses you got
input: the four numbers that build the guess number(the users number)
output: none
*/
void checkHits(int one, int two, int three, int four)
{
	int hits = 0, misses = 0;
	int first = 0, second = 0, third = 0, fourth = 0;
	first = randNum / 1000;
	second = (randNum / 100) % 10;
	third = (randNum / 10) % 10;
	fourth = randNum % 10;
	if(one == first)
		hits++;
	else if(one == second || one == third || one == fourth)
		misses++;
	if(two == second)
		hits++;
	else if(two == first || two == third || two == fourth)
		misses++;
	if(three == third)
		hits++;
	else if(three == second || three == first || three == fourth)
		misses++;
	if(four == fourth)
		hits++;
	else if(four == second || four == third || four == first)
		misses++;
	printf("You got    %d HITS    %d MISSES.\n", hits, misses);
}

/*ask for another game
input: none 
output: none
*/
void end(void)
{
	
}
