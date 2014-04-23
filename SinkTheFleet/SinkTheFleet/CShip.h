//-----------------------------------------------------------------------------
//	File:       CShip.h
//
//	class:		CShip
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
//	class CShip:
//
//	Properties:
//			Ship m_ship - enum of a ship.
//
//	Methods:
//	
//		inline:	
//		CShip(Ship ship = NOSHIP)
//		Constructor - sets the m_ship to Ship Enum.
//
//		void CShip::printName(std::ostream &sout) const
//			prints out shipname to ostream.
//
//		void CCell::print()
//			prints out ship to cout.
//
//		operator Ship() const
//			cast to Ship enum, returns m_ship.
//
//		non-inline:
//					void CShip::print(std::ostream &sout) const;
//						prints out ship to an ostream.
//
//    History Log:
//      3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
#ifndef MB_CSHIP_H
#define MB_CSHIP_H
#include <iostream>
#include <fstream>
#include <string>
#include "textGraphics.h"

namespace MB_CSHIP
{
	enum Ship
	{
		NOSHIP,		 // 0
		MINESWEEPER, // 1 (1-5) -- used only for owner
		SUB,		 // 2
		FRIGATE,	 // 3
		BATTLESHIP,	 // 4
		CARRIER,	 // 5
		HIT,		 // 6 (6-7)-- used only for other side
		MISSED,		 // 7 
	}; 
	const int SHIP_SIZE_ARRAYSIZE = 6; // size of the shipSize array
	const short shipSize[SHIP_SIZE_ARRAYSIZE] = {0, 2, 3, 3, 4, 5}; 
	static const char* shipNames[SHIP_SIZE_ARRAYSIZE] = 
		{"No Ship", "Mine Sweeper", "Submarine", "Frigate", "Battleship", "Aircraft Carrier"};

	class CShip
	{
	public:
		CShip(Ship ship = NOSHIP)
		{m_ship = ship;}

		void CShip::print(std::ostream &sout) const;

		void CShip::print() const
		{print(std::cout);}

		void CShip::printName(std::ostream &sout) const
		{	
			switch(m_ship)
			{
				case MINESWEEPER: sout << "Minesweeper";
					break;
				case SUB: sout << "Submarine";
					break;
				case FRIGATE: sout << "Frigate";
					break;
				case BATTLESHIP: sout << "Battleship";
					break;
				case CARRIER: sout << "Carrier";
					break;
				default: sout << " ";
			}
		}

		operator Ship() const
		{return m_ship;}

	private:
		Ship m_ship;
	};
	std::ostream& operator<<(std::ostream& sout, CShip &ship);
	std::istream& operator>>(std::istream& sin, CShip &ship);
}
#endif