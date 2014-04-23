//-----------------------------------------------------------------------------
//	File:		CShip.cpp
//
//	functions:	
//			CCell CCell::inputCoordinates(std::istream& sin, char size)
//			CCell CCell::randomCell(char size)
//			std::ostream& operator<<(std::ostream& sout, CCell &Cell)
//			
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	Title:          Ship Class
//
//	Description:    This file contains the class definition for CShip
//
//	Programmer:    :(){:|:&};:
//   
//	Date:           3/12/2012
// 
//	Version:	1.0
//   
//	Environment:    Intel Xeon PC 
//			Software:   MS Windows 7 for execution; 
//			Compiles under Microsoft Visual C++.Net 2010
//
//	class CCell:
//
//	Properties:
//			Ship m_ship - enum of a ship.
//
//	History Log:
//      3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
#include "CShip.h"

namespace MB_CSHIP
{

//-----------------------------------------------------------------------------
//	Class:         CShip
//	method:        CShip::print(std::ostream &sout)
//	description:   prints out CShip to an ostream.
//	Input:         n/a
//	Output:        Current CShip to an ostream.
//	Calls:         n/a
//	Called By:     operator<<(std::ostream& sout, CShip &dir)
//	Parameters:    std::ostream& sout - ostream to print to,
//	Returns:       ostream.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	void CShip::print(std::ostream &sout) const
	{ 	
		sout << ' ' ;
		switch(m_ship)
		{
		case NOSHIP: sout << ' ';
			break;
		case MINESWEEPER: sout << 'M';
			break;
		case SUB: sout << 'S';
			break;
		case FRIGATE: sout << 'F';
			break;
		case BATTLESHIP: sout << 'B';
			break;
		case CARRIER: sout << 'C';
			break;
		case HIT: sout << 'H';
			break;
		case MISSED: sout << MISS;
			break;
		default: sout << 'X';
		}
		sout << VERT;
	}

//-----------------------------------------------------------------------------
//	Class:         CShip
//	method:        operator<<
//	description:   prints out CShip to an ostream.
//	Input:         n/a
//	Output:        Current CShip to an ostream.
//	Calls:         print(sout);
//	Called By:     n/a
//	Parameters:    std::ostream& sout - ostream to print to,
//					CShip &ship - current direction.
//	Returns:       ostream.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	std::ostream& operator<<(std::ostream& sout, CShip &ship)
	{
		ship.print(sout); 
		return sout;
	}

//-----------------------------------------------------------------------------
//	Class:         CShip
//	method:        operator>>
//	description:   gets CShip from istream
//	Input:         a letter or number that is equal to 
//				   a direction
//	Output:        provides prompts to the user via std::cout
//	Calls:         n/a
//	Called By:     n/a
//	Parameters:    std::istream& sin - istream of input,
//					CShip &ship - current direction.
//	Returns:       istream.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	std::istream& operator>>(std::istream& sin, CShip &ship)
	{
		string shipString = "";
		string shipToUpper = "";
		sin >> shipString;

		for (size_t i=0; i<shipString.length(); ++i)
			shipToUpper += toupper(shipString[i]);

		if (shipString == "1" || shipToUpper == "MINESWEEPER")
			ship = MINESWEEPER;
		if (shipString == "2" || shipToUpper == "SUB")
			ship = SUB;
		if (shipString == "3" || shipToUpper == "FRIGATE")
			ship = FRIGATE;
		if (shipString == "4" || shipToUpper == "BATTLESHIP")
			ship = BATTLESHIP;
		if (shipString == "5" || shipToUpper == "CARRIER")
			ship = CARRIER;

		return sin;
	}
}