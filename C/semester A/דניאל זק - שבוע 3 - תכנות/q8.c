#include <stdio.h>

#define MONTHS_IN_A_YEAR 12

int main()
{
	//לשנות את הימים שאותו אדם עובד ל24, כי הוא התחיל לעבוד 24 ימים בחודש
	const int DAYS_OF_WORK = 20;
	const float HOURS_OF_WORK = 8.5;
	// כי הוא מקבל את המשכורת ביורו PER_HOUR_IN_EURO לשנות את שם המשתנה ל
	//ובנוסף לשנות את ה 32.3 ל – 8.46 כי 32.3 שקל זה 8.46 יורו
	const float PER_HOUR_IN_SHEKELS = 32.3;
	// כי הוא מקבל את המשכורת ביורו PER_HOUR_IN_EURO ל PER_HOUR_IN_SHEKELS לשנות את שם המשתנה
	float monthSalary = DAYS_OF_WORK * HOURS_OF_WORK * PER_HOUR_IN_SHEKELS;
	printf("his yearly salary:%.2f\n", monthSalary * MONTHS_IN_A_YEAR);
	
	return 0;
}
