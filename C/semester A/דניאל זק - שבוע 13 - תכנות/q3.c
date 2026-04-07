#include <stdio.h>
#include <string.h>

#define MAX_LEGNTH 50
#define NUM_NAMES 10

int findLast(char names[][MAX_LEGNTH], int numOfNames, int maxLenght);
int findFirst(char names[][MAX_LEGNTH], int numOfNames, int maxLenght);
int findLongest(char names[][MAX_LEGNTH], int numOfNames, int maxLenght);
int findShortest(char names[][MAX_LEGNTH], int numOfNames, int maxLenght);

int main()
{
	char names[NUM_NAMES][MAX_LEGNTH] = {0};
	int i = 0;
	int j = 0;
	int rowOfShortest = 0;
	int rowOfLongest = 0;
	int rowOfFirst = 0;
	int rowOfLast = 0;
	
	printf("Enter 10 names:\n");
	for(i = 0; i < NUM_NAMES; i++) 
	{
		fgets(names[i], MAX_LEGNTH, stdin);
		names[i][strcspn(names[i], "\n")] = 0;
    }
	
	rowOfShortest = findShortest(names, NUM_NAMES, MAX_LEGNTH);
	rowOfLongest = findLongest(names, NUM_NAMES, MAX_LEGNTH);
	rowOfFirst = findFirst(names, NUM_NAMES, MAX_LEGNTH);
	rowOfLast = findLast(names, NUM_NAMES, MAX_LEGNTH);
	
	printf("Shortest: %s\nLongest: %s\nFirst: %s\nLast: %s\n", names[rowOfShortest], names[rowOfLongest], names[rowOfFirst], names[rowOfLast]);
	return 0;
}

/*
finds the shortest name
input: names, num of names, max length of the names
output: The row of the shortest name
*/
int findShortest(char names[][MAX_LEGNTH], int numOfNames, int maxLenght)
{
	int count = 0;
	int min = MAX_LEGNTH;
	int rowOfShortest = NUM_NAMES;
	int row = 0;
	int col = 0;
	
	for(row = 0; row < numOfNames; row++)
	{
		count = 0;
		for(col = 0; col < maxLenght; col++)
		{
			if(names[row][col] != 0)
				count++;
			else
				col = MAX_LEGNTH;
		}
		
		if(count < min)
		{
			min = count;
			rowOfShortest = row;
		}
	}
	
	return rowOfShortest;
}

/*
finds the longest name
input: names, num of names, max length of the names
output: The row of the longest name
*/
int findLongest(char names[][MAX_LEGNTH], int numOfNames, int maxLenght)
{
	int count = 0;
	int max = 0;
	int rowOfLongest = NUM_NAMES;
	int row = 0;
	int col = 0;
	
	for(row = 0; row < numOfNames; row++)
	{
		count = 0;
		for(col = 0; col < maxLenght; col++)
		{
			if(names[row][col] != 0)
				count++;
			else
				col = MAX_LEGNTH;
		}
		
		if(count > max)
		{
			max = count;
			rowOfLongest = row;
		}
	}
	
	return rowOfLongest;
}

/*
finds the first name by the alphabet
input: names, num of names, max length of the names
output: The row of the first name by the alphabet
*/
int findFirst(char names[][MAX_LEGNTH], int numOfNames, int maxLenght)
{
	int rowOfFirst = 0;
	int row = 0;
	int col = 0;
	
	for(row = 1; row < numOfNames; row++)
	{
		if(names[row][0] < names[rowOfFirst][0])
			rowOfFirst = row;
		else
		{
			if (strcmp(names[row], names[rowOfFirst]) < 0) 
				rowOfFirst = row;
		}
	}
	
	return rowOfFirst;
}

/*
finds the last name by the alphabet
input: names, num of names, max length of the names
output: The row of the last name by the alphabet
*/
int findLast(char names[][MAX_LEGNTH], int numOfNames, int maxLenght)
{
	int rowOfLast = 0;
	int row = 0;
	int col = 0;
	
	for(row = 1; row < numOfNames; row++)
	{
		if(names[row][0] > names[rowOfLast][0])
			rowOfLast = row;
		else
		{
			if (strcmp(names[row], names[rowOfLast]) > 0)
				rowOfLast = row;
		}
	}
	
	return rowOfLast;
}
