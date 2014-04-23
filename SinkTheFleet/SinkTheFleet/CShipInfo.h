//-----------------------------------------------------------------------------
//	File:       CShipInfo.h
//
//	class:		CShipInfo
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//	Title:          Ship Info Class
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
//	Methods:
//	
//		inline:	
//		CShipInfo::CShipInfo(MB_CSHIP::CShip ship = MB_CSHIP::NOSHIP, 
//		MB_CDIRECTION::CDirection orientation = MB_CDIRECTION::HORIZONTAL, 
//		MB_CCELL::CCell bow = (0,1), short pieces = 0)
//		Constructor - sets all properties of the current ship.
//
//		void print()
//			prints Current CShipInfo's CShip (m_ship) to cout.
//		void print(std::ostream& sout)
//			prints Current CShipInfo's CShip (m_ship) to sout.
//
//		MB_CSHIP::CShip getName()
//			accessor to shipname, returns m_ship.
//		MB_CDIRECTION::CDirection getOrientaion()
//			accessor to ship oritentation, returns m_orientation.
//		MB_CCELL::CCell getBowLocation(){return m_bowLocation;}
//			accessor to ship Bow Location, returns m_bowLocation.
//		short getPiecesLeft(){return m_piecesLeft;}
//			accessor to ship Pieces Left (unsunk), returns m_piecesLeft.
//
//		void setName(MB_CSHIP::CShip param)
//			sets the name of the current CShip (m_ship).
//		void setOrientaion(MB_CDIRECTION::CDirection param)
//			sets the oritentation of the current CShip CDirection (m_orientation).
//		void setBowLocation(MB_CCELL::CCell param)
//			sets the Bow Location of the current CShip CCell (m_bowLocation).
//		void setPiecesLeft(short param)
//			sets the Piece sLeft of the current CShip short (m_piecesLeft).
//
//		non-inline:
//			CShipInfo operator--();
//			bool isSunk();
//
//    History Log:
//      3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
#ifndef CSHIPINFO_H
#define CSHIPINFO_H

#include <cstdlib>
#include <iostream>
#include <exception>
#include "CCell.h"
#include "CShip.h"
#include "CDirection.h"

namespace JP_CSHIPINFO
{
	class CShipInfo
	{
	private:
		MB_CSHIP::CShip m_ship;
		MB_CDIRECTION::CDirection m_orientation;
		MB_CCELL::CCell m_bowLocation;
		short m_piecesLeft;
	public:
		CShipInfo::CShipInfo(MB_CSHIP::CShip ship = MB_CSHIP::NOSHIP, 
			MB_CDIRECTION::CDirection orientation = MB_CDIRECTION::HORIZONTAL, 
			MB_CCELL::CCell bow = (0,1), short pieces = 0)
			:m_ship (ship),
			m_orientation  (orientation),
			m_bowLocation  (bow),
			m_piecesLeft (pieces)
		{}
		void print() {print(std::cout);}
		void print(std::ostream& sout){m_ship.print(sout);}
		MB_CSHIP::CShip getName(){return m_ship;}
		MB_CDIRECTION::CDirection getOrientaion(){return m_orientation;}
		MB_CCELL::CCell getBowLocation(){return m_bowLocation;}
		short getPiecesLeft(){return m_piecesLeft;}
		void setName(MB_CSHIP::CShip param){m_ship = param;}
		void setOrientaion(MB_CDIRECTION::CDirection param){m_orientation = param;}
		void setBowLocation(MB_CCELL::CCell param){m_bowLocation = param;}
		void setPiecesLeft(short param) {m_piecesLeft = param;}
		CShipInfo operator--();
		bool isSunk();
		static const short shipSize[6];
	};
	std::ostream& operator<<(std::ostream& sout, CShipInfo &shipInfo);
}
#endif