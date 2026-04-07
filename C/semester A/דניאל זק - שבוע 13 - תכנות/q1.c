#include <stdio.h>

#define ROWS 5
#define SEATS_IN_ROW 3

#define CHEAP_TICKET_PRICE 25
#define NORMAL_TICKET_PRICE 35
#define VIP_TICKET_PRICE 50

#define ORDERED -1

#define HALL_PRINT 1
#define BUY_SEAT 2
#define TAKEN_SEATS 3
#define AUTOMATIC_CHOSE 4
#define DISCOUNT 5
#define EXIT 6

void printCinema(int cinema[][SEATS_IN_ROW], int rows, int cols);
int welcome();
void applyDiscount(int cinema[][SEATS_IN_ROW], int rows, int cols, int discount);
int mostCheap(int cinema[][SEATS_IN_ROW], int rows, int cols);
int howManyOrdered(int cinema[][SEATS_IN_ROW], int rows, int cols);
int orderSeat(int cinema[][SEATS_IN_ROW], int row, int col);


int main(void)
{
	int cinema[ROWS][SEATS_IN_ROW] = {{CHEAP_TICKET_PRICE, CHEAP_TICKET_PRICE, CHEAP_TICKET_PRICE},
									  {NORMAL_TICKET_PRICE, NORMAL_TICKET_PRICE, NORMAL_TICKET_PRICE},
									  {NORMAL_TICKET_PRICE, VIP_TICKET_PRICE, NORMAL_TICKET_PRICE},
									  {NORMAL_TICKET_PRICE, NORMAL_TICKET_PRICE, NORMAL_TICKET_PRICE},
									  {CHEAP_TICKET_PRICE, CHEAP_TICKET_PRICE, CHEAP_TICKET_PRICE}};
	int choise = 0;
	int row = 0;
	int col = 0;
	int good = 0;
	int count = 0;
	int price = 0;
	int discount = 0;
	
	while(choise != EXIT)
	{
		choise = welcome();
		if(choise == HALL_PRINT)
		{
			printCinema(cinema, ROWS, SEATS_IN_ROW);
		}
		else if(choise == BUY_SEAT)
		{
			printf("Which row (0-4)? ");
			scanf("%d", &row);
			printf("Which seat (0-4)? ");
			scanf("%d", &col);
			good = orderSeat(cinema, row, col);
			if(good == 0)
				printf("Seat taken!\n");
			else
				printf("You got the seat!\n");
		}
		else if(choise == TAKEN_SEATS)
		{
			count = howManyOrdered(cinema, ROWS, SEATS_IN_ROW);
			printf("%d taken seats in the cinema\n", count);
		}
		else if(choise == AUTOMATIC_CHOSE)
		{
			price = mostCheap(cinema, ROWS, SEATS_IN_ROW);
			printf("We picked a seat, the price is %d\n", price); 
		}
		else if(choise == DISCOUNT)
		{
			printf("Enter a discount: ");
			scanf("%d", &discount);
			applyDiscount(cinema, ROWS, SEATS_IN_ROW, discount);
		}
	}
	printf("thank you come again\n");
	
	return 0;
}

/*
Print a cinema hall ticket prices
Input: 	hall, and number of rows, cols
Output: None
*/
void printCinema(int cinema[][SEATS_IN_ROW], int rows, int cols)
{
	int row = 0;
	int col = 0;
	for(row = 0; row < rows; row++) 
	{
		for(col = 0; col < cols; col++)
		{
			printf("%d ", cinema[row][col]);
		}
		printf("\n");
    }
}

/*
order a seat in the cinema
input: hall, row, seat
output: -1 if seat was empty, 0 if already ordered
*/
int orderSeat(int cinema[][SEATS_IN_ROW], int row, int col)
{
	if(cinema[row][col] == ORDERED)
		return 0;
	else
	{
		cinema[row][col] = ORDERED;
		return 1;
	}
}

/*
check how many seats ordered
input: hall, rows, cols
output: how many ordered
*/
int howManyOrdered(int cinema[][SEATS_IN_ROW], int rows, int cols)
{
	int row = 0;
	int col = 0;
	int count = 0;
	for(row = 0; row < rows; row++)
	{
		for(col = 0; col < cols; col++)
		{
			if(cinema[row][col] == ORDERED)
				count += 1;
		}
    }
	return count;
}

/*
find the cheapest seat
input: hall, rows, cols
output: the price of the cheapest
*/
int mostCheap(int cinema[][SEATS_IN_ROW], int rows, int cols)
{
	int row = 0;
	int col = 0;
	int cheapest = VIP_TICKET_PRICE;
	for(row = 0; row < rows; row++) 
	{
		for(col = 0; col < cols; col++)
		{
			if(cinema[row][col] != -1 && cinema[row][col] < cheapest)
				cheapest = cinema[row][col];
		}
    }
	return cheapest;
}

/*
set the discount on all seats
input: hall, rows, cols, discount
output: none
*/
void applyDiscount(int cinema[][SEATS_IN_ROW], int rows, int cols, int discount)
{
	int row = 0;
	int col = 0;
	for(row = 0; row < rows; row++) 
	{
		
		for(col = 0; col < cols; col++)
		{
			if(cinema[row][col] != ORDERED && (cinema[row][col] - discount) > 0)
				cinema[row][col] = cinema[row][col] - discount;
			else if(cinema[row][col] != ORDERED && (cinema[row][col] - discount) < 0)
				cinema[row][col]  = 0;
		}
    }
}
/*
print the welcome screen and get choise ot the function
input: none
output: the choise of the function
*/
int welcome()
{
	int choise = 0;
	do
	{
		printf("\nWelcome to MagshiCinema\nSelect an option:\n1 - Print cinema hall\n2 - Buy a ticket\n3 - Print number of taken seats\n4 - choose a seat automatically\n5 - Set a discount for available all seats\n6 - Exit\n");
		scanf("%d", &choise);
		
		if(choise < 1 || choise > 6)
			printf("Wrong Choice. Enter again\n");
	}
	while(choise < 1 || choise > 6);
	
	return choise;
}
