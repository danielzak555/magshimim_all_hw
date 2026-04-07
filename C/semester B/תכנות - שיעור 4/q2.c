#include <stdio.h>
#include <stdlib.h>

void sortArray(int* arr, int len);

int main(void)
{
    int len = 0, i = 0;
    printf("enter length of array: ");
    scanf("%d", &len);
    int* arr = (int*)malloc(sizeof(int) * len);
	if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Enter %d numbers: \n", len);

    for(i = 0; i < len; i++)
    {
        scanf("%d", (arr + i));
    }

	sortArray(arr, len);

    free(arr);
	getchar();
	getchar();
	return 0;
}

/*
the function sort the array
input: array pointer, size of array in bytes
output: none
*/
void sortArray(int* arr, int len)
{
	int  i = 0, j = 0, minIndex = 0, tmp = 0;
	for (i = 0; i < len- 1; i++)
	{
		// Find the minimum element in the remaining unsorted array 
		minIndex = i;
		for (j = i + 1; j < len; j++)
		{
			if (*(arr + j) < *(arr + minIndex))
			{
				minIndex = j;
			}
		}

		// Swap the found minimum element with the first element 
		tmp = *(arr + minIndex);
		*(arr + minIndex) = *(arr + i);
		*(arr + i) = tmp;
	}

	printf("Sorted:\n");
	for (i = 0; i < len; i++)
	{
		printf("%d ", *(arr + i));
	}
	printf("\n");
}
