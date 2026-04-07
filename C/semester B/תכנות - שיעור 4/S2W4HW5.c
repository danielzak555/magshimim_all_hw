

/*********************************
* Class: MAGSHIMIM C2			 *
* Week 4           				 *
* HW solution   			 	 *
**********************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int* createArr(int len);

int main(void)
{
	int size = 0;
	int* pArr = NULL;//לאתחל לנאל

	printf("Enter a number of cells: ");
	scanf("%d", &size);//לשים אמפרסאנד
    pArr = createArr(size);
	if (pArr == NULL) //להוסיף בדיקה
	{
		printf("Memory allocation failed.\n");
		return 1;
	}
    printf("The array is at address %p: ", pArr);
    free(pArr);
    
	getchar();
	getchar();
	return 0;
}

/*
Function creates an array
input: number of cells in the array
output: pointer to the new array
*/
int* createArr(int size)
{
	int* pArr = (int*)malloc(sizeof(int) * size);//להוסיף את הגודל של כל תא
	if (pArr == NULL) //להוסיף בדיקה
	{
		printf("Memory allocation failed.\n");
		return NULL;
	}
	int i = 0;
	for(i = 0; i < size; i++)
	{
		printf("Please enter a number for index %d: ",i);
		scanf("%d", pArr + i);//לשנות שהמספר יכנס למערך
	}//לא צריך לשחרר את אי
	return pArr;
}
