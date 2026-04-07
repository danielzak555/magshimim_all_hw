#include <stdio.h>
#include <stdlib.h>

#define MIN_ARGC 4

int main(int argc, char** argv)
{
	int i = 2, mul = 1, sum = 0;
    if(argc >= MIN_ARGC)
    {
        if(strcmp(argv[1], "MUL") == 0)
        {
            for (i = 2; i < argc; i++)
            {
                mul *= atoi(argv[i]);
            }
            printf("Result: %d", mul);
        }

        else if(strcmp(argv[1], "ADD") == 0)
        {
            for (i = 2; i < argc; i++)
            {
                sum += atoi(argv[i]);
            }
            printf("Result: %d", sum);
        }
        else
        {
            printf("ERROR! Invalid Command!\nUsage: [ADD | MUL] <number> ... <number>\n");
        }
    }
    else
    {
        printf("ERROR! Invalid Number of Arguments!\nUsage: [ADD | MUL] <number> ... <number>");
    }

    getchar();

	return 0;
}

