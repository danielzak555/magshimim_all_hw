#include <stdio.h>

//השם הזה זה כי אנו סוכמים את האיברים של הסדר עד איבר מסוים אז בשביל שהשם לא יהיה ארוך בחרתי בזה
void sumOfSeries(int first, int ratio, int num);

int main(void)
{
	int first = 0;
	int ratio = 0;
	int num = 0;
	
	printf("Enter first element of the series: ");
	scanf("%d", &first);
	printf("Enter the series ratio: ");
	scanf("%d", &ratio);
	printf("Enter number of elements: ");
	scanf("%d", &num);
    if (num <= 0)
		printf("The sum of the first %d elements is 0", num);
	else
		sumOfSeries(first, ratio, num);
	
	return 0;
}
/*
the function will summerize the the first "num" elementes of the series
input: first - the first num of the series.
       ratio - the number we will multiply the last number of the series to get to the next one.
	   num - the amount of number from the series we will summerize.
output: none.
*/
void sumOfSeries(int first, int ratio, int num) 
{
    int i = 1;
	int sum = 0;
	int previos = first;
	sum += first;
	for(i = 1; i < num; i++)
	{
		sum += previos * ratio;
		previos = previos * ratio;
	}
	printf("The sum of the first %d elements is %d", num, sum);
}
