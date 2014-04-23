//-----------------------------------------------------------------------------
//	File:		CDirection.cpp
//
//	functions:	
//			CDirection::print(std::ostream &sout)
//			operator<<(std::ostream& sout, CDirection &dir)
//			std::ostream& operator<<(std::ostream& sout, CDirection &dir)
//			std::istream& operator>>(std::istream& sin, CDirection &dir)
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	Title:          Direction Class
//
//	Description:    This file contains the class definition for CDirection
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
//	class CDirection:
//
//	Properties:
//			Direction m_direction - Direction of a ship.
//
//	History Log:
//      3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------

#include "CDirection.h"

namespace MB_CDIRECTION
{
//-----------------------------------------------------------------------------
//	Class:         CDirection
//	method:        CDirection::print
//	description:   prints out CDirection to an ostream.
//	Input:         n/a
//	Output:        Current CDirection to an ostream.
//	Calls:         n/a
//	Called By:     operator<<(std::ostream& sout, CDirection &dir)
//	Parameters:    std::ostream& sout - ostream to print to,
//	Returns:       ostream.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	void CDirection::print(std::ostream &sout) const
	{
		if (m_direction == 0)
			sout << 'H';
		else
			sout << 'V';
	}

//-----------------------------------------------------------------------------
//	Class:         CDirection
//	method:        operator<<
//	description:   prints out CDirection to an ostream.
//	Input:         n/a
//	Output:        Current CDirection to an ostream.
//	Calls:         print(sout);
//	Called By:     n/a
//	Parameters:    std::ostream& sout - ostream to print to,
//					CDirection &dir - current direction.
//	Returns:       ostream.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	std::ostream& operator<<(std::ostream& sout, CDirection &dir)
	{
		dir.print(sout); 
		return sout;
	}

//-----------------------------------------------------------------------------
//	Class:         CDirection
//	method:        operator>>
//	description:   gets CDirection from istream
//	Input:         a letter or number that is equal to 
//				   a direction
//	Output:        provides prompts to the user via std::cout
//	Calls:         n/a
//	Called By:     n/a
//	Parameters:    std::istream& sin - istream of input,
//					CDirection &dir - current direction.
//	Returns:       istream.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	std::istream& operator>>(std::istream& sin, CDirection &dir)
	{
		std::string dirString = "";
		std::string dirToUpper = "";
		
		do
		{
		sin >> dirString;

		for (size_t i=0; i<dirString.length(); ++i)
			dirToUpper += toupper(dirString[i]);

		if (dirString == "0" || dirToUpper == "H")
			dir = HORIZONTAL;
		if (dirString == "1" || dirToUpper == "V")
			dir = VERTICAL;
		dirToUpper = "";
		}while(dirString == "0" || dirToUpper == "H" 
			|| dirString == "1" || dirToUpper == "V");

		return sin;
	}
}