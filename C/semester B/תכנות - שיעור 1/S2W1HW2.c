/*********************************
* Class: MAGSHIMIM C2			 *
* Week 1           				 *
* HW Question - Thanks Program 	 *
**********************************/

#include <stdio.h>
#include <string.h>

void printMessage(char str[]);

#define LEN 7

int main(void)
{ 							// לשנות את המספר לקבוע
	char str[LEN] = "THANK ";// הבעייה היא שלמערך אין מקום להוסיף את התו יו לסוף 
	char you = 'u';
	
	strncat(str, &you, 1); // do not fix this line or the next one
	printMessage(str); 
	return 0;
}

/*
the function print thank massage to sigal
input: char str[] - the string to print
output: none
*/
void printMessage(char str[])
{
	printf("Hello Sigal! I just wanted to say that studying with you...\n\n");
	printf("Really made me understand how much I love\n");
	printf(" __  __                 _     _           _           \n");
	printf("|  \\/  |               | |   (_)         (_)          \n");
	printf("| \\  / | __ _  __ _ ___| |__  _ _ __ ___  _ _ __ ___  \n");
	printf("| |\\/| |/ _` |/ _` / __| '_ \\| | '_ ` _ \\| | '_ ` _ \\ \n");
	printf("| |  | | (_| | (_| \\__ \\ | | | | | | | | | | | | | | |\n");
	printf("|_|  |_|\\__,_|\\__, |___/_| |_|_|_| |_| |_|_|_| |_| |_|\n");
	printf("              __/ |                                  \n");
	printf("              |___/                                  \n\n");
	
	printf("Without C you would be just Gal :D\n");
	printf("See you in class!\n");
	printf("and %s !!", str);
	
}