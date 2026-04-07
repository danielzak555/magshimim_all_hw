#include <stdio.h>
#include <stdbool.h>

#define MAXMONTH 12
#define MINMONTH 1
#define MAXDAYSINMONTH 31
#define MINDAYSINMONTH 1
#define MAXWEEKDAY 7
#define MINWEEKDAY 1

enum week{sun = 1, mon, tue, wed, thu, fri, sat};
enum year{jan = 1, feb, mer, apr, may, jun, jul, aug, sep, oct, nov, dec};

int weekDay(int month, int day, int firstday);
bool checkInput(int month, int day, bool flag);

int main()
{
	int day = 0;
	int month = 0;
	int firstDay = 0;
	int theDay = 0;
	bool flag = false;
	printf("Hello! Welcome to the day calculator!\n");
	do
	{
		printf("Enter month to check: (1-Jan, 2-Feb, etc) ");
		scanf("%d", &month);
		printf("Enter day to check: ");
		scanf("%d", &day);
		flag = checkInput(month, day, flag);
		if(flag == true)
		{			
				printf("Enter the weekday of the 1st of the month: (1-Sunday, 2-Monday, etc) ");
				scanf("%d", &firstDay);
				while(MINWEEKDAY > firstDay || MAXWEEKDAY < firstDay)
				{
					printf("Invalid input, try again\n");
					printf("Enter the weekday of the 1st of the month: (1-Sunday, 2-Monday, etc) ");
					scanf("%d", &firstDay);
				}
		}
		else
			printf("Invalid input, try again\n");
	}	
	while(flag == false || MINWEEKDAY > firstDay || MAXWEEKDAY < firstDay);
	
	theDay =  weekDay(month, day, firstDay);
	switch(theDay)
	{
		case sun:
			printf("the %d.%d will be a Sunday", day, month);
			break;
		case mon:
			printf("the %d.%d will be a Monday", day, month);
			break;
		case tue:
			printf("the %d.%d will be a Tuesday", day, month);
			break;
		case wed:
			printf("the %d.%d will be a Wednesday", day, month);
			break;
		case thu:
			printf("the %d.%d will be a Thursday", day, month);
			break;
		case fri:
			printf("the %d.%d will be a Friday", day, month);
			break;
		case sat:
			printf("the %d.%d will be a Saturday", day, month);
			break;		
	}
	return 0;
}

/*
the function finds the num of the day in the week of the day we want to find
input: the num of the month, the day that we want to find his num in the week, the num in the week of the first day in the month
output: the num of the day in the week
*/
int weekDay(int month, int day, int firstDay)
{
		int i = 1;
		int theDay = firstDay;
		for(i = 1; i < day; i++)
		{
			if(theDay == MAXWEEKDAY)
				theDay = 0;
			theDay++;
		}
		
		return theDay;
}
/*
the function checks if the day we entered is not bigger than the amont of the days in the month
input: the mun of the month, the day that we want to check if it fits to the month, the flag that will say if it fits or not
output: the flag that will say if the day fits in the month
*/
bool checkInput(int month, int day, bool flag)
{
	const int maxInMonth28 = 28;
	const int maxInMonth30 = 30;
	const int maxInMonth31 = 31;
		if(month == 2)
		{			
			if(day <= maxInMonth28 && MINDAYSINMONTH <= day)
				flag = true;
		}
		else if(month == 4 || month == 6 || month == 9 || month == 11)
		{
			if(day <= maxInMonth30 && MINDAYSINMONTH <= day)
				flag = true;
		}
		else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if(day <= maxInMonth31 && MINDAYSINMONTH <= day)
				flag = true;
		}
	
	return flag;
}
