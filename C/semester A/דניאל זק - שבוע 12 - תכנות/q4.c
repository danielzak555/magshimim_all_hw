/*********************************
* Class: MAGSHIMIM C1			 *
* Week 11          				 *
**********************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[] = {'H', 'i', ' ', 0};// צריך להוסיף את הנאל 
	char str2[] = {'H', 'o', 0};//צריך לסגור את סוגריי המערך וגם להוסיף נאל
	
	strncat(str1, str2, strlen(str2));// להוריד את האורך של מחרוזת 1 כי אנו רוצים להעתיק את התווים של מחרוזת 2 ולכן יספיק לנו רק האורך שלה
	
	printf("%s", str1);
	return 0;
	
}
