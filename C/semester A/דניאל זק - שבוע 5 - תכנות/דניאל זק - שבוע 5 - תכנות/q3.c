#include <stdio.h>

int main()
{
	float theNumberA = 0;
	float theNumberB = 0;
	int choise = 0;
	  
	printf("enter the first number a: ");
	scanf("%f", &theNumberA);
	printf("enter the first number b: ");
	scanf("%f", &theNumberB);
	
	printf("choose (1) (2) (3) (4)\n1.	adding a+b\n2.	subtracting a-b\n3.	multiplying a*b\n4.	dividing a/b\n");
	scanf("%d", &choise);

	switch (choise)
	{
	case 1:
		printf("the result is: %f\n", theNumberA+theNumberB);
		break; 
	case 2:
		printf("the result is: %f\n", theNumberA-theNumberB);
		break; 
	case 3:
		printf("the result is: %f\n", theNumberA*theNumberB);
		break; 
	case 4:
		if (theNumberB == 0)
			printf("can't divide by zero!!!");
		else
			printf("the result is: %f\n", theNumberA/theNumberB);
		break; 
	default:
		printf("choice is not valid");
	}

	return 0;
}
