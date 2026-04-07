#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STR_LEN 100
#define MIN_BIG_ASCII 65
#define MAX_BIG_ASCII 90
#define MIN_SMALL_ASCII 97
#define MAX_SMALL_ASCII 122
#define MIN_NUMBER_ASCII 48
#define MAX_NUMBER_ASCII 57
#define MAX_LEN 8
#define MIN_LEN 6

int identifyNum(char letter);

bool noDoubles = true;

int main()
{
	char password[STR_LEN] = {0};
	int i = 0;
	char previos = ' ';
	int len = 0;
	int retorn = 0; // retorn just because cant us return
	bool big = false, small = false, number = false;
	
	printf("Enter a password: ");
	fgets(password, STR_LEN, stdin);
	for(i = 0; i < STR_LEN; i++)
	{
		if (password[i] == '\n')
		{
			password[i] = 0;
			break;
		}
	}
	len = strlen(password);
	
	for(i = 0; i < len; i++)
	{
		if(previos == password[i])
		{	
			noDoubles = false;
		}
		previos = password[i];
	}
	
	for (i = 0; i < len; i++)
	{
		retorn = identifyNum(password[i]);
		if(retorn == 1)
		{
			big = true;
		}
		else if(retorn == 2)
		{
			small = true;
		}
		else if(retorn == 3)
		{
			number = true;
		}
	}
	if(big == true && small == true && number == true && len <= MAX_LEN && len >= MIN_LEN && noDoubles == true)
		printf("Yes");
	else
		printf("No");
	
	return 0;
}

/*
the fun will get a char and check if its a big letter small letter or number or other
input: a letter from the password
output: 1 if BIG, 2 if SMALL, 3 if NUMBER, 4 if OTHER
*/
int identifyNum(char letter)
{
	if(letter >= MIN_BIG_ASCII && letter <= MAX_BIG_ASCII)
		return 1;
	else if(letter >= MIN_SMALL_ASCII && letter <= MAX_SMALL_ASCII)
		return 2;
	else if(letter >= MIN_NUMBER_ASCII && letter <= MAX_NUMBER_ASCII)
		return 3;
	else
		return 4;
}
