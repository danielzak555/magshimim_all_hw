#include <stdio.h>

int main(void)
{
	int a = 53, b = 12;
	a = a + b;
	b = a - b;
	a = a - b;
	printf("new a = %d\nnew b = %d\n", a, b);

	return 0;
}
