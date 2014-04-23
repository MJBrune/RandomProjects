//----------------------------------------------------------------------------
// File:	safeio.cpp
// 
// Function:
//      safeChoice
//----------------------------------------------------------------------------

#include "safeio.h"

//---------------------------------------------------------------------------------
// Function: safeChoice(string prompt, char choice1, char choice2)
//
// Title:	safeChoice
//
// Description: 
//			Safely allows user to select one of two characters
//   
// Programmer: Paul Bladek
// 
// Date: 5/1/2006
//
// Version: 1.0
// 
// Environment: Intel Xeon PC 
//                Software:   MS Windows 7 for execution; 
//                Compiles under Microsoft Visual C++.Net 2010
//
// Input:		char input from console
//
// Output:		Screen display of prompt
//
// Calls: none
//
// Called By:	main()
//				setships()
//
//
// Parameters:	prompt: string; prompt for input
//				choice1: char; the default choice
//				choice2: char; the other choice
// 
// Returns:		the character input and validated
//
// History Log:
//   5/1/06 PB completed version 1.0
// ------------------------------------------------------------------------------
char safeChoice(string prompt, char choice1, char choice2)
{
	char input = choice1;
	ostringstream outSStream;
	outSStream << " (" << choice1 << "/" << choice2 << "): " << choice1 << "\b";
	cout << prompt << outSStream.str();
	while((input = toupper(input = cin.get())) != choice1
		&& input != choice2 && input != '\n')
	{
		cin.ignore(BUFFER_SIZE, '\n');
		cout << prompt << outSStream.str();
	}		
	if(input == '\n')
		input = choice1;
	else
		cin.ignore(BUFFER_SIZE, '\n');
	return input;
}




