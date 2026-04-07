#include <stdio.h>
#include <stdbool.h>

#define WIN 100

int main()
{
	const maxInTurn = 10;
	int previos = 0;
	int choise = 0;
	int playerNum = 1;
	bool flag = false;
	do
	{
		printf("Player %d please enter a number: ", playerNum);
		scanf("%d", &choise);
		if(choise <= previos || (choise - previos) > maxInTurn)
		{
			printf("This number is illegal!\n");
		}
		else
		{
			previos =  choise;
			if (WIN <= choise)
			{	
				printf("Player %d wins!", playerNum);
				flag = true;
			}
			else
			{	
				if (playerNum == 1)
					playerNum += 1;
				else
					playerNum -= 1;
					
				printf("Player %d please enter a number: ", playerNum);
				scanf("%d", &choise);
				
				if(choise <= previos || (choise - previos) > maxInTurn)
				{
					while (choise <= previos || (choise - previos) > maxInTurn)
					{
						printf("This number is illegal!\n");
						printf("Player %d please enter a number: ", playerNum);
						scanf("%d", &choise);
					}
				}
				if (!(choise <= previos || (choise - previos) > maxInTurn))
				{
					previos =  choise;
					if (WIN <= choise)
					{	
						printf("Player %d wins!", playerNum);
						flag = true;
					}
					if (playerNum == 1)
						playerNum += 1;
					else
						playerNum -= 1;
				}
			}
		}
	}
	while(flag == false );
	return 0;
}
