#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_FACES 6
#define MAX 6
#define MIN 1

void rollAndCheck(int counters[], int times);
void printResultes(int counters[]);

int main()
{
	int counters[NUM_OF_FACES] = {0};
	int i = 0;
	const int sumOfRolles = 9999;
	srand(time(NULL));
	for(i = 0; i < sumOfRolles; i++)
	{
		rollAndCheck(counters, times);
	}
	printResultes(counters);
}
/*
the function will roll 9999 times nums between 1 to 6 and check how much of every one was rolled
input: the array of the how much times every num was rolled
output: none
*/
void rollAndCheck(int counters[], int times)
{
	int i = 1;
	int flag = 0;
	int randNum = rand() % (MAX - MIN + 1) + MIN;
	int options[NUM_OF_FACES] = {0};
	for(i = 1; i <= NUM_OF_FACES; i++)
	{
		options[i-1] = i;
	}
	i = 0; // refreshing the counter i
	do
	{
		if(options[i] == randNum)
		{
			counters[i] += 1;
			flag += 1;
		}
		else
			i++;
	}
	while(flag == 0);
}
/*
print the resultes of the rolling
input: the array after the resultes already in it
output: none
*/
void printResultes(int counters[])
{
	int i = 0;
	printf("the resultes:\n");
	for(i = 0; i < NUM_OF_FACES; i++)
	{
		printf("the times %d appeared: %d\n", i+1, counters[i]);
	}
}
