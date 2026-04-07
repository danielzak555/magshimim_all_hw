#include <stdio.h>
#include <string.h>

#define STR_LEN 100
#define LETTERS_IN_ABC 26
#define FROM_NUM_TO_CHAR_ASCII 97

int main()
{
	char string[STR_LEN] = {0};
	int frequency[LETTERS_IN_ABC] = {0};
	int i = 0;
	int k = 0;
	int indexInAbc = 0;
	int len = 0;
	int max = 0;
	int secondMax = 0;
	char mostCommon = ' ';
	char secondCommon = ' ';
	
	printf("Enter a string:\n");
	fgets(string, STR_LEN, stdin);
	
	for(i = 0; i < STR_LEN; i++)
	{
		if (string[i] == '\n')
		{
			string[i] = 0;
			break;
		}
	}
	
	len = strlen(string);
	
	for (i = 0; i < len; i++)
	{
		for(k = 0; k < len; k++)
		{
			indexInAbc = string[i] - FROM_NUM_TO_CHAR_ASCII;
			if(string[i] == string[k])
				frequency[indexInAbc]++;
		}
	}
	
	for(i = 0; i < LETTERS_IN_ABC; i++)
	{
		if (frequency[i] > max)
		{
			secondMax = max;
			max = frequency[i];
			secondCommon = mostCommon;
			mostCommon = i + FROM_NUM_TO_CHAR_ASCII;
		}
		
		else if (frequency[i] > secondMax)
		{
			secondMax = frequency[i];
			secondCommon = i + FROM_NUM_TO_CHAR_ASCII;
		}
	}
	
	for(i = 0; i < len; i++)
		if(string[i] == mostCommon)
			string[i] = secondCommon;
		else if(string[i] == secondCommon)
			string[i] = mostCommon;
	
	printf("Most common: %c, 2nd most common: %c\n", mostCommon, secondCommon);
	printf("Swapped:\n");
	printf("%s", string);
	
	return 0;
}
