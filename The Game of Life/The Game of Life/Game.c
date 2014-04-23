#include "Game.h"
void getFirstGen(char fileName[BUFFERLENGTH], int currentGen[][COLS])
{
	FILE *inFileHandle = NULL;
	int i = 0;
	int j = 0;
	int getEachChar = 0;

	inFileHandle = fopen(fileName, "r");

	if(inFileHandle != NULL)
	{
		for (i = 0; i < ROWS; i++)
			{	
				for (j = 0; j < COLS; j++)
				{
					fscanf(inFileHandle, "%d", &getEachChar);
					currentGen[i][j] = getEachChar;
				}					
			}	
	} 
	else 
	{
		fprintf(stderr, "Problem opening file %s", fileName);
		getchar();
		exit(1);
	}
	fclose(inFileHandle);
}

void printGen(int (*currentGenPtr)[COLS])
{
	int i = 0;
	int j = 0;
	
	for( i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			if(currentGenPtr[i][j] == DEAD)
				printf(" ");
			else if(currentGenPtr[i][j] == ALIVE)
				printf("X");			
		}
	printf("\n");
	}
}

//----------------------------------------------------------------------------
//   Function:    GetNeighbourCount()
//
//   Title:       Get Neighbour Count
//
//   Description: calculate the number of neighbours of any one block.
//
//   Programmer:  Michael Brune <admin@mjbrune.org>
//   
//   Date:        11/28/2011
// 
//   Version:     1.0
//  
//   Environment: Intel Xeon PC 
//                Software:   MS Windows 7 for execution; 
//                Compiles under Microsoft Visual Studio.Net 2010
//
//   Input:       na
//
//   Output:      na
//
//   Called By:   GetNeighbours()
//
//   Calls:		  
//
//   Parameters:  
//				const int (*currentGenPtr)[COLS]: Current Gen 
//				int x: X cord to get neighbours from.
//				int y: Y cord to get neighbours from.
// 
//   Returns:     neighbour
//
//   History Log:
//                finished 12/1/11 v1.0 MJB
//                
//                
// ---------------------------------------------------------------------------
int GetNeighbourCount(const int (*currentGenPtr)[COLS], int x, int y)
{
	// so the lowest row we have to check for neighbors is x - 1 because the range of neighbours is only 1 square.
	// the highest row we have to check for neighbors is x + 1 and same for the columns.
	int lowest_row = x - 1;
	int highest_row = x + 1;
	int lowest_col = y - 1;
	int highest_col = y + 1;
	int neighbour = 0;
	highest_row = highest_row > 20 ? 20: x + 1;
	highest_col = highest_col > 40 ? 40: y + 1;	
	
	// loop through only the area we need to. The lowest row and lowest column
	// to the highest row and highest column.
	for( lowest_row = lowest_row < 0 ? 0: x - 1; lowest_row <= highest_row; lowest_row++)
	{
		for( lowest_col = lowest_col < 0 ? 0: y - 1; lowest_col <= highest_col; lowest_col++)
		{
			// when we are looping through, we should check to see if we are at the point are trying to find
			// neighbours for.
			// if we aren't then check to see if grid has an x by it and if so add to the neighbour count.
			if ( lowest_row == x && lowest_col == y);
			else if ( currentGenPtr[lowest_row][lowest_col] == 1 )
			{
				neighbour++;
			}
		}
	}
	return neighbour;
}
//----------------------------------------------------------------------------
//   Function:    nextGen()
//
//   Title:       Get Next Generation
//
//   Description: calculate the next generation
//
//   Programmer:  Johnathan Pickard-Gilyeat 
//   
//   Date:        11/28/2011
// 
//   Version:     1.0
//  
//   Environment: Intel Xeon PC 
//                Software:   MS Windows 7 for execution; 
//                Compiles under Microsoft Visual Studio.Net 2010
//
//   Input:       na
//
//   Output:      na
//
//   Called By:   main()
//
//   Calls:		  
//
//   Parameters:  char oldArray[ROWS][COLS]
// 
//   Returns:     newArray
//
//   History Log:
//				  12/01/11: added support for same gen.
//                finished 11/28/11 v1.0 JPG
//                
//                
// ---------------------------------------------------------------------------
void getNextGen(int (*currentGenPtr)[COLS], int (*nextGenPtr)[COLS])
{
	int i = 0;
	int j = 0;
	int same = 0; 

	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			if (currentGenPtr[i][j] == ALIVE)
			{
				if (GetNeighbourCount(currentGenPtr, i, j) == 2 || 
					GetNeighbourCount(currentGenPtr, i, j) == 3)
					nextGenPtr[i][j] = ALIVE;
				else
					nextGenPtr[i][j] = DEAD;
			}
			if (currentGenPtr[i][j] == DEAD)
			{
				if (GetNeighbourCount(currentGenPtr, i, j) == 3)
					nextGenPtr[i][j] = ALIVE;
				else
					nextGenPtr[i][j] = DEAD;
			}
		}
	}
	
	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			if (currentGenPtr[i][j] == nextGenPtr[i][j])
			{
				same++;
			}
		}
	}
	if (same == MAX)
	{
		printf("The past generation and the next generation is the same");
		getchar();
	}
}
/*void getNextGen(int (*currentGenPtr)[COLS], int (*nextGenPtr)[COLS])
{
	int x = 0;
	int y = 0;
	int neighbors = 0;

	for(x = 0; x < ROWS; x++)
	{
		for(y = 0; y < COLS; y++)
		{
			neighbors = getNeighbors(currentGenPtr, x, y);
			if((currentGenPtr[x][y] == DEAD) && (neighbors == 3))
				nextGenPtr[x][y] = ALIVE;
			else if((currentGenPtr[x][y] == ALIVE) && (neighbors == (2 || 3)))
				nextGenPtr[x][y] = ALIVE;
			else if((currentGenPtr[x][y] == ALIVE) && ((neighbors < 2) || (neighbors >= 4)))
				nextGenPtr[x][y] = DEAD;
		}
	}
}*/
void calculateNextGen(int (*currentGenPtr)[COLS], int (*nextGenPtr)[COLS])
{
	int i = 0;
	int j = 0;

	for(i = 0; i < ROWS; i++)
		for(j = 0; j < COLS; j++)
		{
			if(currentGenPtr[i][j] == 1)
			{
				if(getNeighbors(currentGenPtr,i, j) == 2 || getNeighbors(currentGenPtr, i,
					j) == 3)
					nextGenPtr[i][j] = ALIVE;
				else
					nextGenPtr[i][j] = DEAD;
			}
			else if(currentGenPtr[i][j] == 0)
			{
				if(getNeighbors(currentGenPtr, i, j) == 3)
					nextGenPtr[i][j] = ALIVE;
				else
					nextGenPtr[i][j] = DEAD;
			}
		}
}
int getNeighbors(int (*currentGenPtr)[COLS], int i, int j)
{
    int counter = 0;

    if(i == 0 || j == 0 || i == (ROWS - 1) || j == (COLS - 1))
    {
        if((i == 0) && (j == 0))    //upper left corner
        {
            if(currentGenPtr[0][1] == ALIVE)
				counter++;
			if(currentGenPtr[1][0] == ALIVE)
				counter++;
			if(currentGenPtr[1][1] == ALIVE)
				counter++;
            return counter;
		}
		else if((i == 0) && (j == (COLS - 1))) //upper right corner
		{
			if(currentGenPtr[0][COLS - 1 - 1] == ALIVE)
				counter++;
			if(currentGenPtr[1][COLS - 1] == ALIVE)
				counter++;
			if(currentGenPtr[1][COLS - 1 - 1] == ALIVE)
				counter++;
			return counter;
		}
		else if((i == ROWS - 1) && (j == 0)) //lower left corner
		{
			if(currentGenPtr[ROWS - 1][1] == ALIVE)
				counter++;
			if(currentGenPtr[ROWS - 1 - 1][0] == ALIVE)
				counter++;
			if(currentGenPtr[ROWS - 1 - 1][1] == ALIVE)
				counter++;
			return counter;
		}
		else if((i == ROWS - 1) && (j == COLS - 1)) //lower right corner
		{
			if(currentGenPtr[ROWS - 1 - 1][COLS - 1] == ALIVE)
				counter++;
			if(currentGenPtr[ROWS - 1][COLS - 1 - 1] == ALIVE)
				counter++;
			if(currentGenPtr[ROWS - 1 - 1][COLS - 1 - 1] == ALIVE)
				counter++;
			return counter;
		}
		else if((i == 0) && (j != 0) && (j != COLS - 1)) //top side
		{
			if(currentGenPtr[i][j-1] == ALIVE)
				counter++;
			if(currentGenPtr[i+1][j-1] == ALIVE)
				counter++;
			if(currentGenPtr[i+1][j] == ALIVE)
				counter++;
			if(currentGenPtr[i+1][j+1] == ALIVE)
				counter++;
			if(currentGenPtr[i][j+1] == ALIVE)
				counter++;
			return counter;
		}
		else if((i == ROWS - 1) && (j != 0) && (j != COLS - 1)) //bottom side
		{
			if(currentGenPtr[i][j-1] == ALIVE)
				counter++;
			if(currentGenPtr[i-1][j-1] == ALIVE)
				counter++;
			if(currentGenPtr[i-1][j] == ALIVE)
				counter++;
			if(currentGenPtr[i-1][j+1] == ALIVE)
				counter++;
			if(currentGenPtr[i][j+1] == ALIVE)
				counter++;
			return counter;
		}
		else if((j == 0) && (i != 0) && (i != ROWS - 1)) //left side
		{
			if(currentGenPtr[i-1][j] == ALIVE)
				counter++;
			if(currentGenPtr[i-1][j+1] == ALIVE)
				counter++;
			if(currentGenPtr[i][j+1] == ALIVE)
				counter++;
			if(currentGenPtr[i+1][j+1] == ALIVE)
				counter++;
			if(currentGenPtr[i+1][j] == ALIVE)
				counter++;
			return counter;
		}
		else if ((j == COLS - 1) && (i != 0) & (i != ROWS - 1)) //right side
		{
			if(currentGenPtr[i-1][j] == ALIVE)
				counter++;
			if(currentGenPtr[i-1][j-1] == ALIVE)
				counter++;
			if(currentGenPtr[i][j-1] == ALIVE)
				counter++;
			if(currentGenPtr[i+1][j-1] == ALIVE)
				counter++;
			if(currentGenPtr[i+1][j] == ALIVE)
				counter++;
			return counter;
		}
    }
	else //not on side or corner
	{
		if(currentGenPtr[i][j-1] == ALIVE)
			counter++;
		if(currentGenPtr[i-1][j-1] == ALIVE)
			counter++;
		if(currentGenPtr[i-1][j] == ALIVE)
			counter++;
		if(currentGenPtr[i-1][j+1] == ALIVE)
			counter++;
		if(currentGenPtr[i][j+1] == ALIVE)
			counter++;
		if(currentGenPtr[i+1][j+1] == ALIVE)
			counter++;
		if(currentGenPtr[i+1][j] == ALIVE)
			counter++;
		if(currentGenPtr[i+1][j-1] == ALIVE)
			counter++;
		return counter;
	}
}