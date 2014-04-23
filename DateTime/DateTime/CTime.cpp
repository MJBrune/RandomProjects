#include "CTime.h"
namespace MB_DATETIME
{
	//-----------------------------------------------------------------------------
	//    Class:			CTime
	//		method:			setCurrentTime()
	//
	//		description:	sets the time from the system clock
	//    
	//    Input:			None
	// 
	//    Output:			None
	// 
	//    Calls:            none
	// 
	//    Called By:		constructor, mutators
	// 
	//    Parameters:		none
	// 
	//    Returns:          n/a 
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	void CTime::setCurrentTime()
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_hour = currentTimePtr->tm_hour;
		m_minute = currentTimePtr->tm_min;
		m_second = currentTimePtr->tm_sec;
	}
	// and so on...
	bool CTime::operator==(const Comparable &other)const
	{
		try
		{
			const CTime &otherTime = dynamic_cast<const CTime&>(other);
			if(m_hour == otherTime.m_hour && m_minute ==
				otherTime.m_minute && m_second == otherTime.m_second)
				return true;
			return false;   
		}
		catch(bad_cast e)
		{
			return false;
		}
	}

	bool CTime::operator<(const Comparable &other)const
	{
		try
		{
			const CTime &otherTime = dynamic_cast<const CTime&>(other);
			if(m_hour < otherTime.m_hour || m_minute <
				otherTime.m_minute || m_second < otherTime.m_second)
				return true;
			return false;   
		}
		catch(bad_cast e)
		{
			return false;
		}
	}

	ostream& operator<<(ostream& sout, const CTime& time)
		{time.print(sout); return sout;}
	istream& operator>>(istream& sin, CTime& time)
		{time.input(sin); return sin;}
}