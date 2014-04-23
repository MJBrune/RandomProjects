//-----------------------------------------------------------------------------
//	File:		CCell.cpp
//
//	functions:	
//			CCell CCell::inputCoordinates(std::istream& sin, char size)
//			CCell CCell::randomCell(char size)
//			std::ostream& operator<<(std::ostream& sout, CCell &Cell)
//			
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	Title:          Cell Class
//
//	Description:    This file contains the class definition for CCell
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
//			short m_row,  -- the row number of the cell
//			m_col;    -- the column number of the cell
//
//	History Log:
//      3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
#include "CCell.h"

using namespace std;
namespace MB_CCELL
{
//-----------------------------------------------------------------------------
//	Class:         CCell
//	method:        CCell::inputCoordinates
//	description:   gets cell from istream
//	Input:         a letter and number that is equal to 
//				   the row and column of a cell.
//	Output:        provides prompts to the user via std::cout
//	Calls:         CCell()
//	Called By:     n/a
//	Parameters:    std::istream& sin - istream of input,
//					char size - size of grid;
//	Returns:       CCell of the cell from sin.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	CCell CCell::inputCoordinates(std::istream& sin, char size)
	{
		short numberOfRows = (toupper(size)=='L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(size)=='L') ? LARGECOLS : SMALLCOLS;
		char highChar = static_cast<char>(numberOfRows - 1) + 'A';
		char row  = 'A';
		short col = 0;

		do
		{
			col = 0;
			cout << "Row must be a letter from A to " << highChar 
				<< " and column must be  from 1 to "  << numberOfCols << ": ";
			while((row = toupper(sin.get())) < 'A' || row  > highChar)
			{
				sin.ignore(BUFFER_SIZE, '\n');
				cout << "Row must be a letter from A to " << highChar 
					<< " and column must be  from 1 to "  << numberOfCols << ": ";
			}
			sin >> col;
			if(!sin)
				sin.clear();
			sin.ignore(BUFFER_SIZE, '\n');
		}
		while(col < 1 || col > numberOfCols);
		
		m_row = static_cast<short>(row - 'A');
		m_col = col - 1;
		return CCell(static_cast<short>(row - 'A'), col - 1);
	}
//-----------------------------------------------------------------------------
//	Class:         CCell
//	method:        CCell::randomCell
//	description:   creates, returns and sets the current cell to a random cell.
//	Input:         n/a
//	Output:        n/a
//	Calls:         CCell()
//	Called By:     n/a
//	Parameters:    char size - size of grid.
//	Returns:       Current CCell after setting it to a random cell.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	CCell CCell::randomCell(char size)
	{
		short numberOfRows = (toupper(size)=='L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(size)=='L') ? LARGECOLS : SMALLCOLS;
		srand ( time(NULL) );
		m_row = rand() % numberOfRows;
		m_col = rand() % numberOfCols;
		return CCell(
			m_row , 
			m_col );
	}
//-----------------------------------------------------------------------------
//	Class:         CCell
//	method:        operator<<
//	description:   prints out cell to an ostream.
//	Input:         n/a
//	Output:        Current cell to an ostream.
//	Calls:         print(sout);
//	Called By:     n/a
//	Parameters:    std::ostream& sout - ostream to print to,
//					CCell &Cell - current cell.
//	Returns:       ostream.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	std::ostream& operator<<(std::ostream& sout, CCell &Cell)
		{Cell.print(sout); return sout;}
}