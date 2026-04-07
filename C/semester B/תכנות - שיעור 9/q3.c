#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIDE 8
#define VISITED 1
#define NOT_VISITED 0

#define FIRST_GOAL_X 7
#define FIRST_GOAL_Y 0
#define SECOND_GOAL_X 7
#define SECOND_GOAL_Y 7
#define THIRD_GOAL_X 0
#define THIRD_GOAL_Y 7

#define FALSE 0
#define TRUE !FALSE

bool was_in_first = FALSE;
bool was_in_second = FALSE;
bool was_in_third = FALSE;

void printBoard(int board[][SIDE]);
int goHorsie(int board[][SIDE], int x, int y, int step);

int main(void)
{
	int board[SIDE][SIDE] = { NOT_VISITED };
	if (goHorsie(board, 0, 0, 1))
	{
		printf("Yes, there is a path thru all corners:\n");
		printBoard(board);
	}
	else
	{
		printf("No path that goes thru all corners\n");
	}
	getchar();
	return 0;
}


/*
Function checks if knight can travel from top left corner and travel through all corners
input: the board, and current step
output: whether a path was found
*/
int goHorsie(int board[][SIDE], int x, int y, int step)
{
	if (x >= SIDE || y >= SIDE || x < 0 || y < 0 || // out of the board
		board[x][y] != NOT_VISITED) // we were here already!
		{
			return FALSE;
		}
		
	int res = FALSE;
	bool first = was_in_first;
	bool second = was_in_second;
	bool third = was_in_third;

	if (x == FIRST_GOAL_X && y == FIRST_GOAL_Y)
	{
		board[x][y] = step;
		was_in_first = TRUE;
	}

	if (x == SECOND_GOAL_X && y == SECOND_GOAL_Y)
	{
		board[x][y] = step;
		was_in_second = TRUE;
	}

	if (x == THIRD_GOAL_X && y == THIRD_GOAL_Y)
	{
		board[x][y] = step;
		was_in_third = TRUE;
	}

	if (first && second && third)
	{
		res = TRUE;
	}


	else
	{
		board[x][y] = step;
		step++;
		// changing order here will change the path, because once a condition is verified (TRUE) the rest aren't checked
		res = goHorsie(board, x + 2, y + 1, step) ||
			goHorsie(board, x + 2, y - 1, step) ||
			goHorsie(board, x + 1, y + 2, step) ||
			goHorsie(board, x + 1, y - 2, step) ||
			goHorsie(board, x - 2, y + 1, step) ||
			goHorsie(board, x - 2, y - 1, step) ||
			goHorsie(board, x - 1, y + 2, step) ||
			goHorsie(board, x - 1, y - 2, step);
		if (!res)
		{
			board[x][y] = NOT_VISITED;
			was_in_first = first;
			was_in_second = second;
			was_in_third = third;
		}
	}

	return res;
}


/*
Function prints the board
input: board to print
output: none
*/
void printBoard(int board[][SIDE])
{
	int i = 0, j = 0;
	for (i = 0; i < SIDE; i++)
	{
		for (j = 0; j < SIDE; j++)
		{
			printf("%3d", board[i][j]);
		}
		printf("\n");
	}
}
