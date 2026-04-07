#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN 50

int areValidNumbers(int num1,int num2, int num3);


int main(void)
{
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	int flag = 0;
	do
	{
		srand(time(NULL));
		num1 = rand() % 101 + 1;
		srand(time(NULL));
		num2 = rand() % 101 + 1;
		srand(time(NULL));
		num3 = rand() % 101 + 1;
		flag = areValidNumbers(num1, num2, num3);
	}
	while(flag == 0);
	printf("the first num: %d\n", num1);
	printf("the second num: %d\n", num2);
	printf("the third num: %d\n", num3);
	
	return 0;
}

/*
the fun checks  if the 3 number that was rolled valid to the conditions
input: 3 number that need to check
output: true if they valid and false if not
*/
int areValidNumbers(int num1, int num2, int num3)
{
	int ans = 0;
    if(num1 % 2 == 0 || num2 % 2 == 0 || num3 % 2 == 0)
	{
		if(num1 % 2 == 1 || num2 % 2 == 1 || num3 % 2 == 1)
		{
			if(MIN < num1 || MIN < num2 || MIN < num3)
				ans = 1;
		}
	}
	return ans;
}
