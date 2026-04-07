#include <stdio.h>
#include <stdbool.h>

int main()
{
	int hour = 0;
	int minutes = 0;
	int seconds = 0;
	const minForHour = 0;
	const maxForHour = 23;
	//Min with big M is referenced to minutes and Sec referenced to seconds
	const minForMinAndSec = 0;
	const maxForMinAndSec = 59;
	
	printf("enter yhe time by the pattern hh:mm:ss\n");
	scanf("%2d:%2d:%2d", &hour, &minutes, &seconds);
	
	if (hour >= minForHour && hour <= maxForHour && minutes >= minForMinAndSec && minutes <= maxForMinAndSec && seconds >= minForMinAndSec && seconds <= maxForMinAndSec)
	{
		if (seconds == 59)
		{
			if (minutes == 59)
			{
				if (hour == 23)
				{
					printf("00:00:00\n");
				}
				else
					printf("%d:00:00\n", hour+1);
			}
			else
				printf("%d:%d:00\n", hour, minutes+1);
		}
		else
			printf("%2d:%2d:%2d\n", hour, minutes, seconds+1);
	
	}
	else
		printf("The time isn't valid\n");
	
	return 0;
}
