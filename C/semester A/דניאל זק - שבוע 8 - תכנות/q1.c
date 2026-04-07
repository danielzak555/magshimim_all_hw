#include <stdio.h>

void printNum(int num);

int main(void)
{
	int firstNum = -1;
	int secondNum = 46;
   
	printNum(firstNum);
	printNum(secondNum);
	printNum(firstNum + secondNum);
	printNum(6);
	return 0;
}
/*
function that print the input number.
input: num - the number we will print.
output: none.
*/
void printNum(int num) 
{
    printf("%d\n", num);
} 
