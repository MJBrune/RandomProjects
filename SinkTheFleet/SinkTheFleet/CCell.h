//-----------------------------------------------------------------------------
//	File:       CCell.h
//
//	class:		CCell
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
//	Methods:
//	
//		inline:	
//		CCell (short row = 0, short col = 1)
//		Constructor - sets the Cell row and column
//
//		short CCell::getRow()
//		Accessor - Returns row.
//			
//		short CCell::getCol()
//		Accessor - Returns col.
//
//		void CCell::print(std::ostream &sout)
//			prints out cell to ostream.
//
//		void CCell::print()
//			prints out cell to cout.
//
//		non-inline:
//					CCell CCell::randomCell(char size);
//						sets the current cell as a random sell and returns it.
//					CCell CCell::inputCoordinates(std::istream& sin, char size);
//						Gets cell from istream (usually cin)
//
//    History Log:
//      3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
#ifndef MB_CELL_H
#define MB_CELL_H
#include <iostream>
#include "safeio.h"

const short SMALLROWS = 8;	// number of rows/columns in small sea array 
const short LARGEROWS = 10;	// number of rows/columns in large sea array
const short SMALLCOLS = 12;	// number of rows/columns in small sea array 
const short LARGECOLS = 24;	// number of rows/columns in large sea array

namespace MB_CCELL
{
	class CCell
	{
	public:
		CCell (short row = 0, short col = 1)
			:m_row(row),
			m_col(col)
		{}

		short CCell::getRow()
			{return m_row;}
		short CCell::getCol()
			{return m_col;}

		void CCell::print(std::ostream &sout)
			{std::cout << static_cast<char>(m_row + 'A') << m_col + 1;}

		void CCell::print(){print(std::cout);}

		CCell CCell::randomCell(char size);

		CCell CCell::inputCoordinates(std::istream& sin, char size);

	private:
		unsigned short m_row;	// row
		unsigned short m_col;	// column
	};
	
	std::ostream& operator<<(std::ostream& sout, CCell &Cell);
}
#endif