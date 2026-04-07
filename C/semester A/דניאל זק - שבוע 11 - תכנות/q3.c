#include <stdio.h>
#include <stdlib.h>

#define NUM_GUESTS 200
#define FALSE 	0
#define TRUE !FALSE
#define MAX_KID_AGE 12

float averageAge(int guestAges[], int size);
int howMuchKids(int guestAges[], int size);
int checkSpecificAge(int guestAges[], int size);
int checkTwoOfAge(int guestAges[], int size);
int findYoungest(int guestAges[], int size);
int findOldest(int guestAges[], int size);

int main(void)
{
	int guestAges[NUM_GUESTS] = {42, 108, 95, 101, 90, 5, 79, 79, 83, 105, 66, 66, 2, 28, 2, 12, 116, 63, 28, 37,	
					 112, 85, 63, 34, 53, 23, 22, 117, 39, 96, 48, 7, 12, 19, 70, 113, 108, 20, 116,
					 55, 24, 52, 3, 94, 34, 105, 22, 32, 54, 29, 108, 45, 23, 118, 118, 20, 84, 22,
					 50, 59, 77, 36, 111, 43, 49, 107, 41, 63, 65, 89, 87, 46, 51, 10, 11, 111, 7, 22,
					 34, 69, 70, 24, 85, 35, 37, 81, 47, 57, 12, 29, 25, 40, 27, 44, 18, 59, 39, 43, 
					 10, 102, 34, 36, 80, 19, 25, 91, 100, 27, 114, 67, 102, 66, 45, 113, 31, 70, 18, 
					 94, 58, 73, 107, 91, 42, 37, 36, 48, 16, 95, 72, 53, 111, 71, 22, 5, 47, 71, 28, 
					 72, 8, 58, 98, 48, 34, 64, 66, 30, 50, 39, 102, 109, 63, 107, 27, 71, 94, 9,
					 61, 72, 43, 96, 11, 120, 25, 18, 69, 4, 116, 82, 3, 111, 92, 117, 15, 101, 37, 22, 
					 109, 40, 109, 5, 2, 55, 54, 80, 19, 99, 61, 69, 8, 108, 9, 14, 49, 44, 48, 22, 
					 31, 18, 14, 35};
	float avg = 0;
	int countKids = 0;
	int specificAge = 0;
	int matchFound = 0;
	int minAge = 0;
	int maxAge = 0;
	avg = averageAge(guestAges, NUM_GUESTS);
	printf("Average age: %.2f\n", avg);
	countKids = howMuchKids(guestAges, NUM_GUESTS);
	printf("Number of kids 12 and under: %d\n", countKids);
	specificAge = checkSpecificAge(guestAges, NUM_GUESTS);
	if(FALSE == specificAge)
		printf("No guest this age\n");
	else
		printf("Guest found!\n");
	matchFound = checkTwoOfAge(guestAges, NUM_GUESTS);
	if(FALSE == specificAge)
		printf("No couples found...\n");
	else
		printf("A couple in the same age was found!\n");
	minAge = findYoungest(guestAges, NUM_GUESTS);
	maxAge = findOldest(guestAges, NUM_GUESTS);
	printf("Youngest guest age: %d\n", minAge);
	printf("Oldest guest age: %d\n", maxAge);
	return 0;
}

/*
Function will return average age of party guests
input: age array, number of guests
output: average age
*/
float averageAge(int guestAges[], int size)
{
	float avg = 0;
	int i = 0;
	float sum = 0;
	for(i = 0; i < size; i++)
	{
		sum += guestAges[i];
	}		
	avg = sum / size;
	return avg;
}

/*
the fun will check how much kids under 12 years old
input: the array of ages and the size of it
output: the num of kids under 12 years old
*/
int howMuchKids(int guestAges[], int size)
{
	int count = 0;
	int i = 0;
	for(i = 0; i < size; i++)
	{
		if(guestAges[i] <= MAX_KID_AGE)
			count++;
	}
	
	return count;
}

/*
the fun will check if there is the age we want to find
input: the array of ages and the size of it
output: FALSE if it dont found and true if found
*/
int checkSpecificAge(int guestAges[], int size)
{
	int theAge = 0;
	int found = FALSE;
	int i = 0;
	printf("enter age to find: ");
	scanf("%d", &theAge);
	for(i = 0; i < size; i++)
	{
		if(theAge == guestAges[i])
			found = TRUE;
	}
	
	return found;
}

/*
the fun will check if there is two same ages of a specific age
input: the array of ages and the size of it
output: TRUE if yes and FALSE if not
*/
int checkTwoOfAge(int guestAges[], int size)
{
	int theAge = 0;
	int found = FALSE;
	int count = 0;
	int i = 0;
	const int itsAMatch = 2;
	printf("enter age to find match: ");
	scanf("%d", &theAge);
	for(i = 0; i < size; i++)
	{
		if(theAge == guestAges[i])
			count++;
		if(count == itsAMatch)
		{	
			found = TRUE;
			break;
		}
	}
	
	return found;
}
/*
the fun will find the youngest guest
input: the array of the ages and the size of it
output:the age of the youngest
*/
int findYoungest(int guestAges[], int size)
{
	int i = 0;
	int minAge = guestAges[0];
	for(i = 1; i < size; i++)
	{
		if(guestAges[i] < minAge)
			minAge = guestAges[i];
	}
	
	return minAge;
}
/*
the fun will find the oldest guest
input: the array of the ages and the size of it
output:the age of the oldest
*/
int findOldest(int guestAges[], int size)
{
	int i = 0;
	int maxAge = guestAges[0];
	for(i = 1; i < size; i++)
	{
		if(guestAges[i] > maxAge)
			maxAge = guestAges[i];
	}
	
	return maxAge;
}
