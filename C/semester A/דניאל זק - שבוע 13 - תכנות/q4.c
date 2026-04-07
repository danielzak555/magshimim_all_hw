#include <stdio.h>
#include <string.h>

#define LETTERS 50
#define STR_ROWS 10
#define FROM_NUM_TO_LETTER 97
#define LETTERS_IN_ALPHABET 26

int checkIfPhan(char phanagram[][LETTERS], int maxWords, int alphabet[], int lettersInAlphabet);

int main()
{
	
	char phanagram[STR_ROWS][LETTERS] = {0};
	int alphabet[LETTERS_IN_ALPHABET] = {0};
	int realPhan = checkIfPhan(phanagram, STR_ROWS, alphabet, LETTERS_IN_ALPHABET);
	printf("It's a pangram?\n");
	if(realPhan == 1)
		printf("Yes");
	else
		printf("No");
	
	return 0;
}
/*
will get word until its phanagram
input: the arr where we put the words, the max length of each word
output: 1 if phanagram, 0 if not
*/
int checkIfPhan(char phanagram[][LETTERS], int maxWords, int alphabet[], int lettersInAlphabet)
{
	int word = 0;
	int letter = 0;
	int letterInNumber = 0;
	int i = 0;
	int realPhan = 0;
	int count = 0;
	printf("Enter up to 10 words, try to make a pangram:\n");
	while(realPhan == 0 && count < maxWords)
	{	
		realPhan = 1;
		fgets(phanagram[count], LETTERS, stdin);
		phanagram[count][strcspn(phanagram[count], "\n")] = 0;
		count++;
		for(word = 0; word < maxWords; word++) 
		{
			for(letter = 0; letter < LETTERS; letter++)
			{
				letterInNumber = phanagram[word][letter] - FROM_NUM_TO_LETTER;
				alphabet[letterInNumber] += 1;
			}
		}
		
		for(i = 0;i < lettersInAlphabet; i++)
		{
			if(alphabet[i] == 0)
				realPhan = 0;
		}
	}
	return realPhan;
}
