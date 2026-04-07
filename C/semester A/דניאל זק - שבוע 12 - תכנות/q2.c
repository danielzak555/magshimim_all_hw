#include <stdio.h>
#include <string.h>

#define STR_LEN 100
#define THE_NUM_TO_ASCII 48

int main()
{
	char numInStr[STR_LEN] = {0};
	int num = 0;
	int copyNum = 0;
	int i = 0;
	int len = 0;
	int count = 0;
	char numToChar = ' ';
	printf("Enter num: ");
	scanf("%d", &num);
	copyNum = num;
	if(num < 0)
	{
		numInStr[0] = '-';
		copyNum *= -1;
		num *= -1;
	}
	else if(num > 0)
		numInStr[0] = '+';
	else
		numInStr[0] = '0';
	while(copyNum != 0)
	{
		count++;
		copyNum = copyNum / 10;
	}
	for (i = count; i >= 1; i--)
	{
		numToChar = (num % 10) + THE_NUM_TO_ASCII;
		numInStr[i] = numToChar;
		num = num / 10;
	}
	len = strlen(numInStr);
	printf("string: %s length: %d", numInStr, len);
	
	return 0;
}
