int rollDice(void);
int moveByDice(int location);
int moveIfOnLedderOrSnake(int location);
bool CheckIfWon(int location);

/*
the function will control the game and the switch in the turn of the playes
input : none
output : 0
*/
int main()
{
	...
}

/*
the function will generate the roll of the dice
input : none
output : the num that was generated
*/
int rollDice(void)
{
	...
}

/*
the function will forward the player by the number that generaten in on the dice
input : the num that was generated on the dice, and the corrent num of the square that the player stands on
output : the num of the square that the player stands on after the forwarding
*/
int moveByDice(int location)
{
	...
}

/*
the function will move the player if he stands on the start of the ledder or on the head of the snake
input : the current location of the player
output : the new location of the player if he stands on the start of the ledder or on the head of the snake or the same location if he did not stand on them
*/
int moveIfOnLedderOrSnake(int location)
{
	...
}

/*
the function will check if the player won or not(won if location 100 or more)
input : the loction of the player
output : true if the player won anf false if not
*/
bool CheckIfWon(int location)
{
	...
}