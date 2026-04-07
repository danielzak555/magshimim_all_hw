#include <stdio.h>
#include <string.h>

#define STR_LEN 100
#define MINSMALL 'a'
#define MAXSMALL 'z'
#define MINBIG 'A'
#define MAXBIG 'Z'
#define DIS_BET_SMALL_TO_BIG 32
#define MAX_NUMBER 57
#define MIN_NUMBER 48

int main()
{
	char theStr[STR_LEN] = {0};
	char newStr[STR_LEN] = {0};
	char reversedStr[STR_LEN] = {0};
	int i = 0;
	int k = 0;
	int len = 0;
	int same = 0;
	
	printf("Enter string (max length %d chars):", STR_LEN);
	fgets(theStr, STR_LEN, stdin);
	len = strlen(theStr);
	for(i = 0; i < len; i++) 
	{
		if((theStr[i] >= MINBIG && theStr[i] <= MAXBIG) || (theStr[i] >= MINSMALL && theStr[i] <= MAXSMALL) || (theStr[i] >= MIN_NUMBER && theStr[i] <= MAX_NUMBER))
		{
			if(theStr[i] >= MINBIG && theStr[i] <= MAXBIG)
			{
				theStr[i] = theStr[i] + 32;
			}
			newStr[k] = theStr[i];
			k++;
		}
	}
	
	k = 0;
	
	for(i = len; i >= 0; i--) 
	{
		if((theStr[i] >= MINBIG && theStr[i] <= MAXBIG) || (theStr[i] >= MINSMALL && theStr[i] <= MAXSMALL) || (theStr[i] >= MIN_NUMBER && theStr[i] <= MAX_NUMBER))
		{
			if(theStr[i] >= MINBIG && theStr[i] <= MAXBIG)
			{
				theStr[i] = theStr[i] + 32;
			}
			reversedStr[k] = theStr[i];
			k++;
		}
	}
	printf("%s\n", newStr);
	printf("%s\n", reversedStr);
	same = strcmp(newStr, reversedStr);
	if(same == 0)
		printf("Yes");
	else
		printf("No");
	
	return 0;
}
