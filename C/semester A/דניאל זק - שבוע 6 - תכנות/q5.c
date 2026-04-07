#include <stdio.h>
#include <stdbool.h>

int main() 
{
    int theNumber = 1;
	int i = 0;
	int count = 0;
	bool Prime = true;

    for (theNumber = 2; theNumber <= 1000; theNumber++) 
	{
		Prime = true;
        for (i = 2; i < theNumber; i++) 
		{
            if (theNumber % i == 0) 
			{ 
                Prime = false;
            }
        }

        if (Prime) 
		{
            printf("Prime number: %d\n", theNumber);
			count++;
		}
    }

    printf("Num of primes: %d\n", count);
    return 0;
}
