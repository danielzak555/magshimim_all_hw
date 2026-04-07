#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	int x = 0;
	int y = 0;
	int z = 0;
	int a = 0;
	x = int(getch());
	printf("%d", x);
	y = int(getch());
	printf("%d", y);
	z = int(getch());
	printf("%d", z);
	printf("%d %d %d", x, y, z);
	
	return 0;
}
