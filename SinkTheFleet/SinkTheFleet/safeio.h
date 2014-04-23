#ifndef SAFEIO_H
#define SAFEIO_H
//---------------------------------------------------------------------------------
// File:		textGraphics.h
//
// Function:	template<class T>
//				void safeRead(istream& sin, T& input, const char* prompt) 
//---------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;
const unsigned BUFFER_SIZE = 256;
char safeChoice(string prompt, char choice1 = 'Y', char choice2 = 'N');

template<class T>
void safeRead(istream& sin, T& input, 
	const char* prompt = "invalid input--please input a NUMBER: ");

//---------------------------------------------------------------------------------
// Function:	template<class T>
//				void safeRead(istream& sin, T& input, const char* prompt)
//
// Title:		safeRead
//
// Description: safely reads in a variable (input) from sin.
//		Re-prompts and re-enters if input is invalid  
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
// Input: T& input from istream& sin
//
// Output: Screen display of prompt
//
// Calls: none
//
// Called By: 
//
// Parameters:	istream& sin		-- the input stream
//				T& input			-- theinput variable
//				const char* prompt	-- prompt if not a number
// 
// Returns: none
//
// History Log:
//   5/1/06 PB completed version 1.0
// ------------------------------------------------------------------------------
template<class T>
void safeRead(istream& sin, T& input, const char* prompt)
{
	while(!(sin >> input))		// read in number--enter loop if fail
	{
		sin.clear();		
		sin.ignore(BUFFER_SIZE,'\n');	
		cout << prompt;  
	}
	sin.ignore(BUFFER_SIZE, '\n');  
}
#endif