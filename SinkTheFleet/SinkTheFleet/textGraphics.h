//---------------------------------------------------------------------------------
// File:		textGraphics.h
// 
// Description: declarations for utilizing extended ASCII characters
//	
// Programmer:	Paul Bladek
// 
// Environment: Intel Xeon PC 
//                Software:   MS Windows 7 for execution; 
//                Compiles under Microsoft Visual C++.Net 2010
//---------------------------------------------------------------------------------
#ifndef TEXTGRAPH_H
#define TEXTGRAPH_H
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

// char definitions
const unsigned char UL = 0xda;		// upper left
const unsigned char UR = 0xbf;		// upper right
const unsigned char LL = 0xc0;		// lower left
const unsigned char LR = 0xd9;		// lower right
const unsigned char HORIZ = 0xc4;	// horizontal bar
const unsigned char CR = 0xc3;		// cross to the right
const unsigned char CL = 0xc0;		// cross to the left
const unsigned char CU = 0xc1;		// cross up 
const unsigned char CD = 0xc2;		// cross down
const unsigned char VERT = 0xb3;	// vertical bar
const unsigned char CROSS = 0xc5;	// crosses
const unsigned char MISS = 0xb0;	// screen pattern

const short MAX_LINE_LENGTH = 79;	// longest line allowed
const int OFFSET = 2;				// number of start & end chars

// prints the top line of a box
void boxTop(ostream& sout, unsigned short length);
// prints the bottom line of a box
void boxBottom(ostream& sout, unsigned short length);
// prints text line of a box
void boxLine(ostream& sout, const string& text, unsigned short length, 
			 unsigned char alignment = 'L', char fillc = ' ' ); 

#endif