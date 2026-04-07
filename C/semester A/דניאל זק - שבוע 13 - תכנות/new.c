#include <stdio.h>

#define STR_COLS 8
#define STR_ROWS 8

int main()
{
	char damka[STR_ROWS][STR_COLS] = {' '};
	int i = 0;
	int j = 0;
	int count = 0;
	int even = 1;
	
	for(i = 0; i < STR_ROWS; i++) 
	{
		
		for(j = 0; j < STR_COLS; j++)
		{
			if((i+j) % 2 == 0)
				damka[i][j] = 'b';
			else
				damka[i][j] = 'w';
			printf("%c ", damka[i][j]);
		}
		printf("\n");
    }
	
	return 0;
}
