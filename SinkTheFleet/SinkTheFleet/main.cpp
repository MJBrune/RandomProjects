#include "CSinkTheFleet.h"

int main()
{
	CSinkTheFleet game;
	char again = 'Y';
	int winner = 0;

	do
	{
	winner = game.play();

	cout << "Congratulations player " << winner + 1 << "!";

	again = safeChoice("Would you like to play again?", 'Y', 'N');

	} while(toupper(again) == 'Y');

	return EXIT_SUCCESS;

}