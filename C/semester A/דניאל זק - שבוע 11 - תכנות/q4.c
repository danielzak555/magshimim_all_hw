#include <stdio.h>
#include <stdlib.h>

#define ARR_LENGTH 2
//צריך לשנות את שם המערך כי לא הגיוני צריך להוריד סוגריים מרובעות כי אינט זה לא מערך ובנוסף לשנות את סוג הפלט של הפונקציה לואויד כי  לא מחזירה כלום
void getGrades(int arr[]);
void printGrades(int first, int second);

int main(void)
{
	int myGrades[] = {0,0};
	//לשנות שם פונקציה
	getGrades(myGrades);
	//כאנו צריכים לשים סוגריים מרובעות ואת המיקום של הציון במערך כי ככה אנו מקבלים את המיקום של המערך בזיכרון
	int first = myGrades[0];
	int second = myGrades[1];	
	
	printGrades(first, second);
	return 0;
}
//לשנות את הפלט לשום דבר
/*
Function will change values of array (input from user)
input: array to change
output:none
*/
//לשנות שם פונקציה ולהוריד את הסוגריים המרובעות אחרי האינט ולשנות את סוג הפונקציה לואויד
void getGrades(int arr[])
{
	printf("Enter grades in English and history: ");
	scanf("%d %d", &arr[0], &arr[1]);
	// להוריד את ההחזרה של ערך כי כאשר אנו משנים ערך במערך זה ביי רפרנס ולכן זה משנה אותו ישירות במערך ולא צריך להחזיר את המערך ישרות
}

/*
Function will print two grades
input: the grades to print
output: none
*/
void printGrades(int first, int second)
{
	printf("My grade in English is: %d!\n",first);
	printf("My grade in History is %d! Great Success!\n",second);
}
