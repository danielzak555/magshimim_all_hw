#include <stdio.h>

#define MAX 5

void printOffset(int arrNumbers[], int offset);

int main()
{
	int offset = 0;
	int arrNumbers[MAX] = {0};
	printf("Enter 5 numbers to array: ");
	scanf("%d %d %d %d %d", &arrNumbers[0], &arrNumbers[1], &arrNumbers[2], &arrNumbers[3], &arrNumbers[4]);
	printf("\n");
	printf("Enter offset: ");
	scanf("%d", &offset);
	printf("\n");
	printOffset(arrNumbers, offset);
	
	return 0;
}
/*
print the numbers with the offset
input: the array of the 5 numbers and the offset
output: none
*/
void printOffset(int arrNumbers[], int offset)
{
	int count = 1;
	int secondOffset = offset - 1;
	printf("Array with offset of %d: ", offset);
	while(count <= MAX)
	{
		if(secondOffset < MAX - 1)
		{
			secondOffset++;
			printf("%d ", arrNumbers[secondOffset]);
			count++;
		}
		else
		{
			secondOffset = 0;
			printf("%d ", arrNumbers[secondOffset]);
			count++;
		}			
	}
}
