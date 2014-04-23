#include "Game.h"

int main(void)
{
	int currentGen[ROWS][COLS];
	int nextGen[ROWS][COLS];
	char fileName[BUFFERLENGTH];

	int (*currentGenPtr)[COLS] = currentGen;
	int (*nextGenPtr)[COLS] = nextGen;
	int (*temp)[COLS] = NULL;

	puts("\"The Game of Life\" by Code Monkeys of Awesomeness");
	puts("Please enter the name of the file");

	fgets(fileName, BUFFERLENGTH, stdin);
	if(fileName[strlen(fileName)-1] == '\n')
		fileName[strlen(fileName)-1] = '\0';
	else
		while(getchar() != '\n');

	getFirstGen(fileName, currentGen);
	printGen(currentGenPtr);

	while(getchar() == '\n')
	{
		system("cls");
		getNextGen(currentGenPtr, nextGenPtr);
		//calculateNextGen(currentGenPtr, nextGenPtr);

		temp = currentGenPtr;
		currentGenPtr = nextGenPtr;
		nextGenPtr = temp;

		printGen(currentGenPtr);
	}

	return EXIT_SUCCESS;
}