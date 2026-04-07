#include <stdio.h>
#include <stdbool.h>

int main()
{
	char x = ' ';
	
	printf("enter a letter\n");
	x = getchar();
	
	printf(x == 'C' ? "UPPER" : x == 'c' ? "LOWER" : "illegal character");
	
	return 0;
}
