#include <stdio.h>

#define COURSES 3
#define EXERCISES 11

int main(void)
{
	//הבעיה היא בכך שדניאל החתיך אתחל את המערך כך ששלושת האיברים הראשונים בשורה הראשונה יהיו הציונים ולא האיבר הראשון בכל שורה
	int myGrades[COURSES][EXERCISES] = {{80}, {60}, {70}};
	int i = 0;
	int j = 0;
	
	for(i = 0; i < COURSES; i++)
	{
		for(j = 0; j < EXERCISES; j++)
		{
			printf("%d ", myGrades[i][j]);
		}
		printf("\n");
	}
	return 0;
}
/*
המערך יראה כך

{80,60,70,0,0,0,0,0,0,0,0}
{0,0,0,0,0,0,0,0,0,0,0}
{0,0,0,0,0,0,0,0,0,0,0}
*/
