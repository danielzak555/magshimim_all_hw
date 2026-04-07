#include <stdio.h>
#include <stdbool.h>

int main()
{
	char x = ' ';
	
	printf("enter a letter\n");
	x = getchar();
	
	if (x == 'C')
		printf("UPPER\n");
	else if (x == 'c')
		printf("LOWER\n");
	else
		printf("illegal character\n");
	
	return 0;
}
