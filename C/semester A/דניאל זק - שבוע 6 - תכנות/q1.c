#include <stdio.h>

#define MAX 1000
#define MIN 1

int main()
{
	int theNumber = 0;
	
	do
	{
		printf("enter a number\n");
		scanf("%d", &theNumber);
		
		if(theNumber > MAX || theNumber < MIN || theNumber % 2 != 0)
			printf("number is illegal or not even so enter enother one\n");
	}
	while(theNumber > MAX || theNumber < MIN || theNumber % 2 != 0);
		
	printf("your number is legal and its even\n");
	
	return 0;
}
