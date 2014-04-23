#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <exception>
#include "Comparable.h"
#include <iomanip>
using namespace std;

namespace MB_DATETIME
{
	
	const short MAXHOUR = 24;
    const short MAXMINSEC = 60;
	const short MINHOURMINSEC = 0;
//-----------------------------------------------------------------------------
//    Class:			CTime
//
//    File:             CTime.cpp
//
//    Title:            CTime Class
//
//    Description:		This file contains the class definition for CTime
//
//    Programmer:		Paul Bladek
//   
//    Date:             4/7/2008
// 
//    Version:          1.0
//  
//    Environment:   Hardware: IBM Pentium  
//                   Software:  WinXP or later or .NET for execution;
//
//    Compiles under Microsoft C++ 2005
// 
//	  class Date:
//
//	  Properties:
//			int m_hour		-- 0 - 23
//			int m_minute	-- 0 - 59
//			int m_second	-- 0 - 59 
//
//	  Methods:
//			Inline:
//				short getHour()const    -- accessor for m_hour
//				short getMinute()const  -- accessor for m_minute  
//				short getSecond()const  -- accessor for m_second
//
//			Non-inline:
//					
//				virtual bool equals(const Comparable &other)const
//				virtual lessthan(const Comparable &other)const
//				virtual void input(istream& sin)
//				virtual void print(ostream& sout)const
//
//				void setHour(short hour)
//				void setMinute(short minute)
//				void setSecond(short second)
//				void print(ostream& sout)const
//
//    History Log:
//                      4/7/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
	class CTime : virtual public Comparable
	{
	public:
		CTime(void)
			{setCurrentTime();}
		CTime(int hour, int minute = MINHOURMINSEC, int second = MINHOURMINSEC)
		{
			setCurrentTime();
			if (hour >= MINHOURMINSEC && hour < MAXHOUR)
				m_hour = hour;
			if (minute >= MINHOURMINSEC && minute < MAXMINSEC)
				m_minute = minute;
			if (second >= MINHOURMINSEC && second < MAXMINSEC)
				m_second = second;
		}

		// pure virtuals that MUST be defined		
		virtual void input(istream& sin)
			{ int hour, minute, second;
			sin >> hour; sin.ignore(); sin >> minute; sin.ignore(); sin >> second; 
			*this = CTime(hour, minute, second);}
		virtual void print(ostream& sout)const
			{sout << std::setw(2) << std::setfill('0') << m_hour << ":" 
			<< std::setw(2) << std::setfill('0') << m_minute << ":" 
			<< std::setw(2) << std::setfill('0') << m_second;}
		virtual bool operator==(const Comparable &other)const;
		virtual bool operator!=(const Comparable &other)const
			{return !((*this) == other);}
		virtual bool operator<(const Comparable &other)const;
		virtual bool operator>(const Comparable &other)const
			{return !((*this) < other) && !((*this) == other);}
		virtual bool operator<=(const Comparable &other)const
			{return !((*this) > other);}
		virtual bool operator>=(const Comparable &other)const
			{return !((*this) < other);}

		// Accessors
		short getHour()const {return m_hour;}
		short getMinute()const {return m_minute;}
		short getSecond()const {return m_second;}

		// Mutators
		void setHour(short hour);
		void setMinute(short minute);
		void setSecond(short second);

		void setCurrentTime(void);
		virtual ~CTime() {}

	protected:
		int m_hour;
		int m_minute;
		int m_second;
	};
	
	ostream& operator<<(ostream& sout, const CTime& time);
	istream& operator>>(istream& sin, CTime& time);
}