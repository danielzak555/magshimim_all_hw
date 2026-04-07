#include <stdio.h>

int main()
{
	int age_grandm = 70;
	int age_grandf = 72;
	int age_cousin1 = 16;
	int age_cousin2 = 27;
	int age_cousin3 = 34;
	int sum_ages_grandparents = age_grandm + age_grandf;
	int sum_ages_cousins = age_cousin1 + age_cousin2 + age_cousin3;
	printf("age of grandmother:%d\nage of grandfather:%d\n", age_grandm, age_grandf);
	printf("age of first cousin:%d\nage of second cousin:%d\nage of third cousin:%d\n", age_cousin1, age_cousin2, age_cousin3);
	printf("sum of ages of grandparents:%d\n", sum_ages_grandparents);
	printf("sum of ages of cousins:%d\n", sum_ages_cousins);

	return 0;
}
