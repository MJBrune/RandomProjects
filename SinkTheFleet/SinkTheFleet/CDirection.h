//-----------------------------------------------------------------------------
//	File:       CDirection.h
//
//	class:		CDirection
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
//	Methods:
//	
//		inline:	
//		CDirection (Direction dir)
//		Constructor - sets the Direction with the direction enum.
//
//		operator Direction() const
//		cast to Direction, return m_direction.
//
//		void CCell::print()
//			prints out direction to cout.
//
//		non-inline:
//					void CDirection::print(std::ostream &sout) const;
//
//    History Log:
//      3/12/12  FB  completed version 1.0
//-----------------------------------------------------------------------------
#ifndef MB_CDIR_H
#define MB_CDIR_H
#include <iostream>
#include <string>
#include "safeio.h"

namespace MB_CDIRECTION
{
	enum Direction
	{
		HORIZONTAL, // 0
		VERTICAL	// 1
	};
	class CDirection
	{
	public:
		CDirection (Direction dir)
			:m_direction (dir)
		{}
		operator Direction() const
			{return m_direction;}

		void CDirection::print(std::ostream &sout) const;

		void CDirection::print() const
		{print(std::cout);}


	private:
		Direction m_direction;
	};
	std::ostream& operator<<(std::ostream& sout, CDirection &dir);
	std::istream& operator>>(std::istream& sin, CDirection &dir);
}
#endif