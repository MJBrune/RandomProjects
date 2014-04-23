//-----------------------------------------------------------------------------
//	File:		CShipInfo.cpp
//
//	functions:	
//			CCell CCell::inputCoordinates(std::istream& sin, char size)
//			CCell CCell::randomCell(char size)
//			std::ostream& operator<<(std::ostream& sout, CCell &Cell)
//			
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	Title:         Ship Info Class
//
//	Description:    This file contains the class definition for CShipInfo
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
//	class CShipInfo:
//
//	Properties:
//					MB_CSHIP::CShip m_ship; - object of current ship.
//					MB_CDIRECTION::CDirection m_orientation; - orientation of current ship
//					MB_CCELL::CCell m_bowLocation; - bow location of current ship
//					short m_piecesLeft; - piece left of the current ship
//
//	History Log:
//      3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
#include "CShipInfo.h"

namespace JP_CSHIPINFO
{
//-----------------------------------------------------------------------------
//	Class:         CShipInfo
//	method:        CShipInfo::operator--
//	description:   operator -- for Cshipinfo, minuses one from m_piecesLeft
//	Input:         n/a
//	Output:        n/a
//	Calls:         n/a
//	Called By:     n/a
//	Parameters:    n/a
//	Returns:       this after m_piecesLeft -1;
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	CShipInfo CShipInfo::operator--()
	{
		this->m_piecesLeft -= 1;
		return *this;
	}
//-----------------------------------------------------------------------------
//	Class:         CShipInfo
//	method:        CShipInfo::isSunk()
//	description:   operator -- for Cshipinfo, minuses one from m_piecesLeft
//	Input:         n/a
//	Output:        n/a
//	Calls:         n/a
//	Called By:     n/a
//	Parameters:    n/a
//	Returns:       true if m_piecesLeft is 0, otherwise false.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	bool CShipInfo::isSunk()
	{
		if(this->m_piecesLeft == 0)
			return true;
		return false;
	}

//-----------------------------------------------------------------------------
//	Class:         CShipInfo
//	method:        operator<<
//	description:   prints out CShipInfo to an ostream.
//	Input:         n/a
//	Output:        Current CShipInfo to an ostream.
//	Calls:         print(sout);
//	Called By:     n/a
//	Parameters:    std::ostream& sout - ostream to print to,
//					CShipInfo &ShipInfo - current ShipInfo Object.
//	Returns:       ostream.
//	History Log:
//	               3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
	std::ostream& operator<<(std::ostream& sout, CShipInfo &ShipInfo)
		{ShipInfo.print(sout); return sout;}
}