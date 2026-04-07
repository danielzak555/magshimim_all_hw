#include <stdio.h>
#include <stdbool.h>

int main()
{
	int choise = 0;
	int mulOdd = 1;
	int mulEven = 1;
	int i = 1;
	int digit = 0;
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;
	bool flag4 = false;
	bool flag5 = false;
	bool flag6 = false;
	bool flag7 = false;
	bool flag8 = false;
	bool flag9 = false;
	bool flag0 = false;
	
	do
	{
		printf("Please enter a number\n");
		scanf("%d", &choise);
		if(choise < 1)
		{
			printf("This number is illegal!\n");
		}
		else
		{
			while(i <= choise)
			{
				digit = (choise % (i * 10)) / i;
				i = i * 10;
				switch(digit)
				{
					case 1:
						if(!(flag1))
							mulOdd = mulOdd * digit;
						flag1 = true;
						break;
					case 2:
						if(!(flag2))
							mulEven = mulEven * digit;
						flag2 = true;
						break;
					case 3:
						if(!(flag3))
							mulOdd = mulOdd * digit;
						flag3 = true;
						break;
					case 4:
						if(!(flag4))
							mulEven = mulEven * digit;
						flag4 = true;
						break;
					case 5:
						if(!(flag5))
							mulOdd = mulOdd * digit;
						flag5 = true;
						break;
					case 6:
						if(!(flag6))
							mulEven = mulEven * digit;
						flag6 = true;
						break;
					case 7:
						if(!(flag7))
							mulOdd = mulOdd * digit;
						flag7 = true;
						break;
					case 8:
						if(!(flag8))
							mulEven = mulEven * digit;
						flag8 = true;
						break;
					case 9:
						if(!(flag9))
							mulOdd = mulOdd * digit;
						flag9 = true;
						break;
					case 0:
						if(!(flag0))
							mulEven = mulEven * digit;
						flag0 = true;
						break;
				}
			}
		}
	}
	while(choise < 1);
	printf("Product of distinct even digits is %d\n", mulEven);
	printf("Product of distinct odd digits is %d\n", mulOdd);
	return 0;
}
