#include <stdio.h>

#define COLS 10
#define ROWS 10

#define MAX_WITH_ONE_NUMBER 9
#define MAX_WITH_TWO_NUMBERS 99

int main()
{
	int mulTable[ROWS][COLS] = {0};
	int i = 0;
	int j = 0;
	
	for(i = 0; i < ROWS; i++) 
	{
		for(j = 0; j < COLS; j++)
		{
			if(i == 0)
				mulTable[i][j] = j + 1;
			else if(j == 0)
				mulTable[i][j] = i + 1;
			else
				mulTable[i][j] = (i + 1) * (j + 1);
			if(mulTable[i][j] <= MAX_WITH_ONE_NUMBER)
				printf(" ");
			if(mulTable[i][j] <= MAX_WITH_TWO_NUMBERS)
				printf(" ");
			printf("%d ", mulTable[i][j]);
		}
		printf("\n");
    }
	
	return 0;
}
